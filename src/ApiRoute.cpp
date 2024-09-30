#include "ApiRoute.h"

#include <charconv>

#include <magic_enum.hpp>
#include <nlohmann/json.hpp>

#include <ocpp/types/OcppActionCentralSystem.h>

#include "ChargePointRepository.h"
#include "utils/log.h"

using json = nlohmann::json;
using namespace ocpp::types;

ApiRoute::ApiRoute(crow::SimpleApp& app,
                   ChargePointRepository& chargePoints)
    : _app(app),
      _chargePoints(chargePoints) {
    CROW_WEBSOCKET_ROUTE(_app, "/api")
        .onopen([&](crow::websocket::connection& conn) {
            info << conn.get_remote_ip() << "> new client";
            _apiClients.add(&conn);
            _apiClients.send(_chargePoints.chargePoints(), &conn);
            _apiClients.send(_chargePoints.configurations(), &conn);
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
            info << "client closed: " << reason;
            _apiClients.remove(&conn);
        })
        // message from API client shall be connection agnostic
        .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary) {
            if (!is_binary) {
                return onAction(data);
            }

            info << "received " << data.size() << " bytes";
            return onBinary(data);
        })
        .onerror([&](crow::websocket::connection& conn, const std::string& data) {
            error << "error: " << data;
            _apiClients.remove(&conn);
        });

    _chargePoints.propertiesObservable().subscribe([&](const std::map<std::string, Properties>& properties) {
        _apiClients.send(properties);
    });
    _chargePoints.configurationObservable().subscribe([&](const std::map<std::string, ConfigurationKeys>& configuration) {
        _apiClients.send(configuration);
    });
}

void ApiRoute::onAction(const std::string& data) {
    json j = json::parse(data);
    if (!j.is_array() || j.size() != 4) {
        warning << "api> unexpected message: " << data;
        return;
    }

    auto action = magic_enum::enum_cast<OcppActionCentralSystem>(j[0]);
    if (!action.has_value()) {
        warning << "api> unknown action: " << data;
        return;
    }

    switch (action.value()) {
    case OcppActionCentralSystem::TriggerMessage:
        info << "api> action: " << data;
        _chargePoints.triggerMeterValues();
        break;
    case OcppActionCentralSystem::ChangeConfiguration: {
        auto key = magic_enum::enum_cast<ConfigurationKey>(j[2]);
        if (!key.has_value()) {
            warning << "api> unknown configuration key: " << j[2];
            return;
        }
        info << "api> action: " << data;
        // TODO
        //_chargePoints.changeConfigurationById(j[1], key.value(), j[3]);
        break;
    }
    default:
        warning << "api> unhandled action: " << data;
        break;
    }
}

void ApiRoute::onBinary(const std::string& data) {
    json j = json::from_cbor(data.begin(), data.end());
    for (const auto& cp : j.items()) {
        for (const auto& prop : cp.value().items()) {
            int result;
            auto [ptr, ec] = std::from_chars(prop.key().data(), prop.key().data() + prop.key().size(), result);
            if (ec == std::errc()) {
                const auto key = static_cast<PropertyKey>(result);
                switch (prop.value().type()) {
                case json::value_t::string:
                    info << cp.key() << "> " << magic_enum::enum_name(key) << ": " << prop.value();
                    _chargePoints.setPropertiesById(cp.key(), {{key, prop.value().get<std::string>()}});
                    break;
                case json::value_t::number_integer:
                case json::value_t::number_unsigned:
                    info << cp.key() << "> " << magic_enum::enum_name(key) << ": " << prop.value();
                    _chargePoints.setPropertiesById(cp.key(), {{key, prop.value().get<int>()}});
                    break;
                default:
                    warning << cp.key() << "> unexpected property type> " << magic_enum::enum_name(prop.value().type());
                    break;
                }
            } else if (prop.key() == "configuration") {
                onOcppConfiguration(cp.key(), prop.value());
            } else {
                warning << "api> unexpected key: " << prop.key();
            }
        }
    }
}

void ApiRoute::onProperty(const json& j) {
    for (const auto& cp : j.items()) {
        for (const auto& prop : cp.value().items()) {
            const auto key = static_cast<PropertyKey>(std::stoi(prop.key()));
            switch (prop.value().type()) {
            case json::value_t::string:
                info << cp.key() << "> " << magic_enum::enum_name(key) << ": " << prop.value();
                _chargePoints.setPropertiesById(cp.key(), {{key, prop.value().get<std::string>()}});
                break;
            case json::value_t::number_integer:
            case json::value_t::number_unsigned:
                info << cp.key() << "> " << magic_enum::enum_name(key) << ": " << prop.value();
                _chargePoints.setPropertiesById(cp.key(), {{key, prop.value().get<int>()}});
                break;
            default:
                warning << cp.key() << "> unexpected property type> " << magic_enum::enum_name(prop.value().type());
                break;
            }
        }
    }
}

void ApiRoute::onOcppConfiguration(const std::string& id, const nlohmann::json& j) {
    for (const auto& confs : j.items()) {
        const auto confKey = static_cast<ConfigurationKey>(std::stoi(confs.key()));
        std::vector<OcppMeasurand> measurands;
        for (const auto& measurandItem: confs.value().items()) {
            measurands.push_back(static_cast<OcppMeasurand>(std::stoi(measurandItem.key())));
        }
        _chargePoints.setConfigurationById(id, {{confKey, measurands}});
    }
}
