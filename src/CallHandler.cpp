#include "CallHandler.h"

#include <cstdlib>

#include <crow.h>
#include <magic_enum.hpp>

#include "ocpp/calls/OcppMeterValues.h"
#include "ocpp/types/OcppActionCentralSystem.h"
#include "ocpp/types/OcppMeasurand.h"

#include "ChargePointRepository.h"
#include "utils/Overload.h"

using namespace crow::json;
using namespace ocpp;
using namespace ocpp::types;

CallHandler::CallHandler(ChargePointRepository& repository)
    : _repository(repository) {}

bool CallHandler::onCall(void* userData, const OcppMessage& message) {
    crow::websocket::connection& conn = *static_cast<crow::websocket::connection*>(userData);

    return std::visit(utils::Overload {
        [](const OcppCallResult&) {
            return false;
        },
        [](std::nullopt_t) {
            return false;
        },
        [&](const calls::OcppMeterValues& call) {
            return onMeterValues(call, conn);
        },
        [&](const OcppCall<OcppActionChargePoint>& call) {
            switch (call.action) {
            case OcppActionChargePoint::BootNotification: return onBootNotification(call.payload, conn);
            case OcppActionChargePoint::Heartbeat: return onHeartbeat(call.payload, conn);
            case OcppActionChargePoint::StatusNotification: return onStatusNotification(call.payload, conn);
            //case OcppActionChargePoint::MeterValues: return onMeterValues(call.payload, conn);
            // FirmwareStatusNotification can be handled with onStatusNotification
            case OcppActionChargePoint::FirmwareStatusNotification: return onStatusNotification(call.payload, conn);
            case OcppActionChargePoint::StartTransaction: return onStartTransaction(call.payload, conn);
            case OcppActionChargePoint::StopTransaction: return onStopTransaction(call.payload, conn);
            /*case ocpp::OcppActionType::Authorize:
            case ocpp::OcppActionType::StopTransaction:
            */
            default: return false;
            }
        },

    }, message);
}

void CallHandler::sendGetConfiguration(crow::websocket::connection& conn) {
    OcppCall<OcppActionCentralSystem> payload {
        OcppMessageType::Call,
        "GetConfiguration " + std::to_string(++_transactionId),
        OcppActionCentralSystem::GetConfiguration,
        {
            { OcppCallPayloadKey::key, "GetConfigurationMaxKeys" }
        }};
    conn.send_text(payload.toBuffer());
}

// TODO: remove these handlers and do the type safe way like for MeterValues
bool CallHandler::onBootNotification(const OcppCallPayload& payload, crow::websocket::connection& conn) {
    if (!payload.contains(OcppCallPayloadKey::chargePointModel) ||
        !payload.contains(OcppCallPayloadKey::chargePointSerialNumber)) {
        return false;
    }

    if (!payload.at(OcppCallPayloadKey::chargePointModel).is_string() ||
        !payload.at(OcppCallPayloadKey::chargePointSerialNumber).is_string()) {
        return false;
    }

    const auto id = payload.at(OcppCallPayloadKey::chargePointModel).get<std::string>() +
                    "_" + payload.at(OcppCallPayloadKey::chargePointSerialNumber).get<std::string>();
    _repository.add({&conn, id, id});

    sendGetConfiguration(conn);

    return true;
}

bool CallHandler::onHeartbeat(const OcppCallPayload& payload, crow::websocket::connection& conn) {
    return false;
}

bool CallHandler::onStatusNotification(const OcppCallPayload& payload, crow::websocket::connection& conn) {
    if (!payload.contains(OcppCallPayloadKey::status)) {
        return false;
    }
    auto statusEnum = magic_enum::enum_cast<OcppCallStatus>(payload.at(OcppCallPayloadKey::status).get<std::string>());
    if (!statusEnum.has_value()) {
        return false;
    }

    _repository.setPropertiesByIp(&conn, {{PropertyKey::status, statusEnum.value()}});
    return true;
}

bool CallHandler::onMeterValues(const calls::OcppMeterValues& call, crow::websocket::connection& conn) {
    // Get the last element (largest key-value pair)
    auto lastElement = call.meterValues.rbegin(); // reverse iterator to the last element
    if (lastElement == call.meterValues.rend()) {
        return false;
    }

    for (const auto& kv : lastElement->second.sampledValues) {
        CROW_LOG_INFO << "ocpp> " << conn.get_remote_ip() << "> " << magic_enum::enum_name(kv.first) << ": " << kv.second.value;

        switch (kv.first) {
        case types::OcppMeasurand::PowerActiveImport:
            _repository.setPropertiesByIp(&conn, {{PropertyKey::power, (int)kv.second.value}});
            break;
        case types::OcppMeasurand::PowerOffered:
            _repository.setPropertiesByIp(&conn, {{PropertyKey::powerOffered, (int)kv.second.value}});
            break;
        }
    }

    return true;
}

bool CallHandler::onStartTransaction(const OcppCallPayload& payload, crow::websocket::connection& conn) {
    return true;
}

bool CallHandler::onStopTransaction(const OcppCallPayload& payload, crow::websocket::connection& conn) {
    return true;
}
