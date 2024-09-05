#include "ActionHandler.h"

#include <cstdlib>

#include <crow.h>
#include <magic_enum.hpp>

#include "ChargePointRepository.h"

using namespace crow::json;
using namespace ocpp;

ActionHandler::ActionHandler(ChargePointRepository& repository)
    : _repository(repository) {}

bool ActionHandler::onCall(const ocpp::OcppCall& call, void* userData) {
    crow::websocket::connection& conn = *static_cast<crow::websocket::connection*>(userData);

    switch (call.action) {
        case ocpp::OcppActionType::BootNotification: return onBootNotification(call.payload, conn);
        case ocpp::OcppActionType::Heartbeat: return onHeartbeat(call.payload, conn);
        case ocpp::OcppActionType::StatusNotification: return onStatusNotification(call.payload, conn);
        case ocpp::OcppActionType::MeterValues: return onMeterValues(call.payload, conn);
        // FirmwareStatusNotification can be handled with onStatusNotification
        case ocpp::OcppActionType::FirmwareStatusNotification: return onStatusNotification(call.payload, conn);
        case ocpp::OcppActionType::StartTransaction: return onStartTransaction(call.payload, conn);
        /*case ocpp::OcppActionType::Authorize:
            onAuthorize(call);
            break;
        case ocpp::OcppActionType::StartTransaction:
            onStartTransaction(call);
            break;
        case ocpp::OcppActionType::StopTransaction:
            onStopTransaction(call);
            break;
        */
    }

    return false;
}

bool ActionHandler::onBootNotification(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn) {
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
    _repository.add({conn, id, id});
    return true;
}

bool ActionHandler::onHeartbeat(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn) {
    return false;
}

bool ActionHandler::onStatusNotification(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn) {
    if (!payload.contains(OcppCallPayloadKey::status)) {
        return false;
    }
    auto statusEnum = magic_enum::enum_cast<ocpp::OcppCallStatus>(payload.at(OcppCallPayloadKey::status).get<std::string>());
    if (!statusEnum.has_value()) {
        return false;
    }

    _repository.setPropertiesByIp(conn, {{PropertyKey::status, statusEnum.value()}});
    return true;
}

bool ActionHandler::onMeterValues(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn) {
    if (!payload.contains(ocpp::OcppCallPayloadKey::connectorId) ||
        !payload.contains(ocpp::OcppCallPayloadKey::meterValue)) {
        return false;
    }
    if (!payload.at(ocpp::OcppCallPayloadKey::connectorId).is_number() ||
        !payload.at(ocpp::OcppCallPayloadKey::meterValue).is_array() ||
        payload.at(ocpp::OcppCallPayloadKey::meterValue).empty()) {
        return false;
    }

    // Extract connectorId from payload
    const auto connectorId = payload.at(ocpp::OcppCallPayloadKey::connectorId).get<int>();
    if (connectorId < 0) {
        return false;
    }

    const auto lastValue = payload.at(ocpp::OcppCallPayloadKey::meterValue).back();
    if (!lastValue.contains("timestamp") ||
        !lastValue.contains("sampledValue")) {
        return false;
    }
    if (!lastValue.at("timestamp").is_string() ||
        !lastValue.at("sampledValue").is_array() ||
        lastValue.at("sampledValue").empty()) {
        return false;
    }

    const auto sampledValue = lastValue.at("sampledValue");
    // Convert sampledValue from array to object

    // Extract power from payload
    std::optional<double> power;
    // {"value":"0.00","measurand":"Power.Active.Import","unit":"W"}
    for (const auto& it : sampledValue) {
        if (!it.contains("value") ||
            !it.contains("unit") ||
            !it.contains("measurand") ||
            it.contains("phase") ||
            it.at("measurand").get<std::string>() != "Power.Active.Import") {
            continue;
        }

        power = std::atof(it.at("value").get<std::string>().c_str());
    }

    if (!power.has_value()) {
        return false;
    }

    _repository.setPropertiesByIp(conn, {{PropertyKey::power, (int)power.value()}});

    return true;
}

bool ActionHandler::onStartTransaction(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn) {
    return true;
}
