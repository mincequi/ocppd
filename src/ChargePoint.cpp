#include "ChargePoint.h"

#include <crow/websocket.h>

#include <ocpp/OcppCall.h>
#include <ocpp/types/OcppActionCentralSystem.h>
#include <ocpp/types/OcppChargingProfile.h>

#include <utils/log.h>

using namespace ocpp;
using namespace ocpp::types;

ChargePoint::ChargePoint(crow::websocket::connection* connection, const std::string& id, const std::string& name)
    : _connection(connection), _id(id) {
    _properties[PropertyKey::name] = name;
}

bool ChargePoint::operator==(const ChargePoint& cp) const {
    return _connection == cp._connection;
}

std::string ChargePoint::remoteIp() const {
    return _connection->get_remote_ip();
}

const Properties& ChargePoint::properties() const {
    return _properties;
}

void ChargePoint::setProperties(const Properties& properties) {
    for (const auto& [key, value] : properties) {
        _properties[key] = value;

        switch (key) {
        case PropertyKey::powerOffered: sendPowerOffered(std::get<int>(value)); break;
        default: break;
        }
    }
}

const OcppConfiguration& ChargePoint::configuration() const {
    return _configuration;
}

void ChargePoint::setConfiguration(const OcppConfiguration& configuration) {
    for (const auto& [key, value] : configuration) {
        _configuration[key] = value;
    }
}

void ChargePoint::sendPowerOffered(int powerOffered) {
    static int _powerOffered = 0;
    return;


    nlohmann::json chargingProfile = {
        {"chargingProfileId", 1},
        {"stackLevel", 0},
        {"chargingProfilePurpose", "TxProfile"},
        {"chargingProfileKind", "Absolute"},
        {"chargingSchedule", {
                                 {"chargingRateUnit", "A"},
                              {"chargingSchedulePeriod", nlohmann::json::array({{
                                                                {"startPeriod", 0},
                                                                {"limit", 8},
                                                                {"numberPhases", 3}
                                                            }})}
                             }}
    };

    nlohmann::json remoteStartTransaction = {
        2,                      // Message Type ID for Request
        "uniqueId123",           // Unique ID for the request
        "RemoteStartTransaction", // Action
        {                         // Payload
            {"idTag", "user123"},  // ID representing the user or vehicle
            {"connectorId", 1},    // Connector ID (optional)
            {"chargingProfile", chargingProfile}  // Optional charging profile
        }
    };

    return _connection->send_text(remoteStartTransaction.dump());


    OcppCall<OcppActionCentralSystem> call {
        OcppMessageType::Call,
        "RemoteStartTransaction " + std::to_string(++_powerOffered),
        OcppActionCentralSystem::RemoteStartTransaction,
        { { OcppCallPayloadKey::idTag, "user" },
          { OcppCallPayloadKey::connectorId, 1 },
         { OcppCallPayloadKey::chargingProfile, chargingProfile }
        }
    };

    auto buffer = call.toBuffer();
    info << "Sending RemoteStartTransaction: " << buffer;
    if (powerOffered > 1380) {
        _connection->send_text(buffer);
    }
}
