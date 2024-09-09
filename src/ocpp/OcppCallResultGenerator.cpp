#include "OcppCallResultGenerator.h"

#include <magic_enum.hpp>

#include <chrono>
#include <iomanip>
#include <sstream>

#include <ocpp/types/OcppCallResultPayloadKey.h>
#include <ocpp/types/OcppCallResultStatus.h>

namespace ocpp {

using namespace types;
using json = nlohmann::json;

OcppCallResultGenerator::OcppCallResultGenerator() {}

OcppCallResult OcppCallResultGenerator::generate(const OcppCall<OcppActionChargePoint>& call) {
    OcppCallResult::Payload payload;

    switch (call.action) {
    case OcppActionChargePoint::BootNotification:
        payload[OcppCallResultPayloadKey::status] = (std::string)magic_enum::enum_name(OcppCallResultStatus::Accepted);
        payload[OcppCallResultPayloadKey::currentTime] = now();
        payload[OcppCallResultPayloadKey::interval] = 60;
        break;
    case OcppActionChargePoint::Heartbeat:
        payload[OcppCallResultPayloadKey::currentTime] = now();
        break;
    case OcppActionChargePoint::StartTransaction:
        payload[OcppCallResultPayloadKey::transactionId] = rand() % 1000000;
        payload[OcppCallResultPayloadKey::idTagInfo] = json{
            {"status", "Accepted"},
        };
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
