#include "OcppConfFactory.h"

#include <magic_enum.hpp>

#include <chrono>
#include <iomanip>
#include <sstream>

#include <ocpp/confs/OcppConfStatus.h>
#include <ocpp/types/OcppConfPayloadKey.h>

namespace ocpp {

using namespace confs;
using namespace types;
using json = nlohmann::json;

OcppConfBase OcppConfFactory::build(const reqs::OcppReq& req, WebSocketConnection& conn) {
    return std::visit([&](auto&& req) -> OcppConfBase {
        using T = std::decay_t<decltype(req)>;  // Deduce the actual type of the request
        auto it = _handlers.find(typeid(T));    // Find the handler for the request type
        if (it != _handlers.end()) {
            return it->second(req, conn);  // Call the appropriate handler
        } else {
            const auto& baseReq = static_cast<const reqs::OcppReqBase<OcppActionChargePoint>&>(req);
            OcppConfBase::Payload payload;
            switch (baseReq.action) {
            case OcppActionChargePoint::BootNotification:
                payload[OcppConfPayloadKey::status] = (std::string)magic_enum::enum_name(OcppConfStatus::Accepted);
                payload[OcppConfPayloadKey::currentTime] = now();
                payload[OcppConfPayloadKey::interval] = 60;
                break;
            case OcppActionChargePoint::Heartbeat:
                payload[OcppConfPayloadKey::currentTime] = now();
                break;
            case OcppActionChargePoint::StartTransaction:
                payload[OcppConfPayloadKey::transactionId] = rand() % 1000000;
                payload[OcppConfPayloadKey::idTagInfo] = json{ {"status", "Accepted"} };
                break;
            case OcppActionChargePoint::DiagnosticsStatusNotification:
            case OcppActionChargePoint::FirmwareStatusNotification:
            case OcppActionChargePoint::MeterValues:
            case OcppActionChargePoint::StatusNotification:
                break;
            default:
                warn("unhandled req type: " + std::string(magic_enum::enum_name(baseReq.action)));
                break;
            }
            return OcppConfBase{baseReq.id, payload};
        }
    }, req);
}

std::string OcppConfFactory::now() {
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
