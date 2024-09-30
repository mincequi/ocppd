#include "OcppReqHandler.h"

#include <cstdlib>

#include <crow.h>
#include <magic_enum.hpp>

#include "ocpp/reqs/OcppReq.h"
#include "ocpp/types/OcppActionCentralSystem.h"
#include "ocpp/types/OcppMeasurand.h"
#include "ocpp/utils/overload.h"

#include "ChargePointRepository.h"

using namespace crow::json;
using namespace ocpp;
using namespace ocpp::types;

namespace ocpp {

OcppReqHandler::OcppReqHandler(ChargePointRepository& repository)
    : _repository(repository) {}

void OcppReqHandler::process(reqs::OcppReq& ocppReq, WebSocketConnection& conn) {
    return std::visit([&](auto&& req) {
        using T = std::decay_t<decltype(req)>;  // Deduce the actual type of the request
        auto it = _handlers.find(typeid(T));    // Find the handler for the request type
        if (it != _handlers.end()) {
            it->second(req, conn);  // Call the appropriate handler
        } else {
            switch (req.action) {
            case OcppActionChargePoint::Heartbeat:
                break;
            default:
                warn("unhandled req type: " + std::string(magic_enum::enum_name(req.action)));
                break;
            }
        }
    }, ocppReq);
}

void OcppReqHandler::sendGetConfiguration(crow::websocket::connection& conn) {
    reqs::OcppReqBase<OcppActionCentralSystem> payload2 {
                                               "ChangeConfiguration " + std::to_string(++_transactionId),
                                               OcppActionCentralSystem::ChangeConfiguration,
                                               {
                                                   { OcppReqPayloadKey::key, "MeterValuesSampledData" },
                                                   { OcppReqPayloadKey::value, "Voltage,Current.Offered,Energy.Active.Import.Register,Power.Active.Import,Power.Offered,SoC" }
                                               }};
    conn.send_text(payload2.toBuffer());

    reqs::OcppReqBase<OcppActionCentralSystem> payload3 {
                                               "ChangeConfiguration " + std::to_string(++_transactionId),
                                               OcppActionCentralSystem::ChangeConfiguration,
                                               {
                                                   { OcppReqPayloadKey::key, "MeterValuesAlignedData" },
                                                   { OcppReqPayloadKey::value, "Voltage,Current.Offered,Energy.Active.Import.Register,Power.Active.Import,Power.Offered" }
                                               }};
    conn.send_text(payload3.toBuffer());

    reqs::OcppReqBase<OcppActionCentralSystem> payload {
        "GetConfiguration " + std::to_string(++_transactionId),
        OcppActionCentralSystem::GetConfiguration,
        {
            { OcppReqPayloadKey::key, "GetConfigurationMaxKeys" }
        }};
    conn.send_text(payload.toBuffer());
}

} // namespace ocpp
