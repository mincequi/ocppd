#include "OcppCallResultGenerator.h"

#include <magic_enum.hpp>

#include <chrono>
#include <iomanip>
#include <sstream>

#include <ocpp/OcppCallResultPayloadKey.h>
#include <ocpp/OcppCallResultStatus.h>

namespace ocpp {

OcppCallResultGenerator::OcppCallResultGenerator() {}

OcppCallResult OcppCallResultGenerator::generate(const OcppCall& call) {
    OcppCallResult::Payload payload;

    switch (call.action) {
    case OcppActionType::BootNotification:
        payload[OcppCallResultPayloadKey::status] = (std::string)magic_enum::enum_name(OcppCallResultStatus::Accepted);
        payload[OcppCallResultPayloadKey::currentTime] = now();
        payload[OcppCallResultPayloadKey::heartbeatInterval] = 60;
        break;
    case OcppActionType::Heartbeat:
        payload[OcppCallResultPayloadKey::currentTime] = now();
        break;
    }

    return OcppCallResult{call.id, payload};
}

std::string OcppCallResultGenerator::now() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* utc_time = std::gmtime(&now_time_t);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    // Format the UTC time in ISO 8601 format
    std::ostringstream oss;
    oss << std::put_time(utc_time, "%Y-%m-%dT%H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << ms.count() << 'Z';
    return oss.str();
}

} // namespace ocpp
