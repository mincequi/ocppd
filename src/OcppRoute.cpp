#include "OcppRoute.h"

#include <ocpp/types/OcppActionCentralSystem.h>

#include "ChargePointRepository.h"

#include "utils/log.h"

using namespace ocpp;

OcppRoute::OcppRoute(crow::SimpleApp& app,
                     ChargePointRepository& chargePoints) :
    _app(app),
    _chargePoints(chargePoints),
    _reqHandler(_chargePoints),
    _confHandler(_chargePoints),
    _service(_confHandler, _reqHandler, _confFactory) {

    _reqHandler.on<reqs::BootNotification>([this](const reqs::BootNotification& req, WebSocketConnection& conn) {
        auto& cp = static_cast<ChargePoint&>(conn);
        auto id = req.chargePointModel + "_" + req.chargePointSerialNumber;
        std::transform(id.begin(), id.end(), id.begin(), ::tolower);
        if (_chargePoints.add({cp._connection, id, id})) {
            info << "new ChargePoint: " << id;
            reqs::OcppReqBase<OcppActionCentralSystem> payload {
                OcppMessageType::Call,
                std::to_string(rand()),
                OcppActionCentralSystem::GetConfiguration,
                {
                    { OcppReqPayloadKey::key, "GetConfigurationMaxKeys" }
                }};
            cp.send(payload.toBuffer());
        }
    }).on<reqs::StatusNotification>([this](const reqs::StatusNotification& req, WebSocketConnection& conn) {
        const auto& cp = static_cast<ChargePoint&>(conn);
        _chargePoints.setPropertiesByIp(cp._connection, {{PropertyKey::status, req.status},
                                                         {PropertyKey::errorCode, req.errorCode}});
    }).on<reqs::MeterValues>([this](const reqs::MeterValues& req, WebSocketConnection& conn) {
        // Get the last element (largest key-value pair)
        auto lastElement = req.meterValues.rbegin(); // reverse iterator to the last element
        if (lastElement == req.meterValues.rend()) {
            return;
        }

        Properties properties;
        std::vector<double> voltages;
        for (const auto& kv : lastElement->second.sampledValues) {
            switch (kv.first) {
            case types::OcppMeasurand::PowerActiveImport:
                properties[PropertyKey::power] = (int)kv.second.value;
                break;
            case types::OcppMeasurand::PowerOffered:
                properties[PropertyKey::powerOffered] = (int)kv.second.value;
                break;
            case types::OcppMeasurand::VoltageL1:
            case types::OcppMeasurand::VoltageL2:
            case types::OcppMeasurand::VoltageL3:
                voltages.push_back(kv.second.value);
                break;
            default:
                break;
            }
        }
        if (properties.empty()) {
            return;
        }
        if (voltages.size() == 3) {
            properties[PropertyKey::voltage] = (int)std::round(std::accumulate(voltages.begin(), voltages.end(), 0.0f) / voltages.size());
        }

        const auto& cp = static_cast<ChargePoint&>(conn);
        _chargePoints.setPropertiesByIp(cp._connection, properties);
    });

    _confHandler.on<ConfigurationKeys>([this](const ConfigurationKeys& conf, WebSocketConnection& conn) {
        const auto& cp = static_cast<ChargePoint&>(conn);
        _chargePoints.setConfigurationByIp(cp._connection, conf);
    });

    _service.onInfo([this](const Emitter::Info& i) {
        switch (i.severity) {
        case Emitter::Info::Severity::Info:
            CROW_LOG_INFO << i.message;
            break;
        case Emitter::Info::Severity::Warning:
            CROW_LOG_WARNING << i.message;
            break;
        case Emitter::Info::Severity::Error:
            CROW_LOG_ERROR << i.message;
            break;
        }
    });

    CROW_WEBSOCKET_ROUTE(app, "/ocpp")
        .onopen([&](crow::websocket::connection& conn) {
            //info << conn.get_remote_ip() << "> new client";
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
            std::lock_guard<std::mutex> _(_mutex);
            info << "> client closed: " << reason;
            _chargePoints.removeByIp(&conn);
        })
        .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
            std::lock_guard<std::mutex> _(_mutex);
            if (is_binary) {
                warning << conn.get_remote_ip() << "> unexpected binary message";
                return;
            }

            auto chargePoint = _chargePoints.byConn(&conn);
            if (!chargePoint) {
                info << conn.get_remote_ip() << "> new client";
                ChargePoint newChargePoint(&conn, "", "");
                _service.process(data, newChargePoint);
            } else {
                _service.process(data, *chargePoint);
            }
        })
        .onerror([&](crow::websocket::connection& conn, const std::string& data) {
            std::lock_guard<std::mutex> _(_mutex);
            error << "> error: " << data;
            //_chargePoints.removeByIp(&conn);
        });
}
