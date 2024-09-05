#include "ApiRoute.h"

#include <magic_enum.hpp>
#include <nlohmann/json.hpp>

#include "ChargePointRepository.h"

using json = nlohmann::json;

ApiRoute::ApiRoute(crow::SimpleApp& app,
                 ChargePointRepository& chargePoints)
    : _app(app),
      _chargePoints(chargePoints) {
    CROW_WEBSOCKET_ROUTE(_app, "/api")
        .onopen([&](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "api> " << conn.get_remote_ip() << "> new client";
            _apiClients.add(&conn);
            sendChargePoints(conn);
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
            CROW_LOG_INFO << "api> " << conn.get_remote_ip() << "> client closed: " << reason;
            _apiClients.remove(&conn);
        })
        .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
            if (!is_binary) {
                CROW_LOG_WARNING << "api> " << conn.get_remote_ip() << "> unexpected string message";
                return;
            }

            CROW_LOG_INFO << "api> " << conn.get_remote_ip() << "> received bytes: " << data.size();

            // Decode from CBOR
            json j = json::from_cbor(data.begin(), data.end());
            for (const auto& cp : j.items()) {
                for (const auto& prop : cp.value().items()) {
                    const auto key = static_cast<PropertyKey>(std::stoi(prop.key()));
                    switch (prop.value().type()) {
                        case json::value_t::string:
                            CROW_LOG_INFO << "api> " << cp.key() << "> " << magic_enum::enum_name(key) << ": " << prop.value();
                            _chargePoints.setPropertiesById(cp.key(), {{key, prop.value().get<std::string>()}});
                            break;
                        case json::value_t::number_integer:
                            CROW_LOG_INFO << "api> " << cp.key() << "> " << magic_enum::enum_name(key) << ": " << prop.value();
                            _chargePoints.setPropertiesById(cp.key(), {{key, prop.value().get<int>()}});
                            break;
                        default:
                            CROW_LOG_WARNING << "api> " << cp.key() << "> unexpected property value type> " << magic_enum::enum_name(key) << prop.value();
                            break;
                    }
                }
            }
        })
        .onerror([](crow::websocket::connection& conn, const std::string& data) {
            CROW_LOG_ERROR << "api> " << conn.get_remote_ip() << "> error: " << data;
        });

    _chargePoints.chargePointsObservable().subscribe([&](const ChargePoints& chargePoints) {
        _apiClients.broadcast(chargePoints);
    });
}

void ApiRoute::sendChargePoints(crow::websocket::connection& conn) {
    // Encode to CBOR
    json j;
    for (const auto& cp : _chargePoints.chargePoints()) {
        for (const auto& prop : cp.second) {
            std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                j[cp.first][std::to_string(magic_enum::enum_integer(prop.first))] = arg;
            }, prop.second);
        }
    }

    CROW_LOG_INFO << "api> " << conn.get_remote_ip() << "> sending charge points: " << j.dump();
    const auto buffer = json::to_cbor(j);
    conn.send_binary({buffer.begin(), buffer.end()});
}
