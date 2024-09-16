#include "OcppReqParser.h"

#include <cstdlib>

#include <crow.h>
#include <magic_enum.hpp>

#include "ocpp/types/OcppActionCentralSystem.h"
#include "ocpp/types/OcppMeasurand.h"
#include "ocpp/types/OcppMessage.h"
#include "ocpp/utils/overload.h"

#include "ChargePointRepository.h"

using namespace crow::json;
using namespace ocpp;
using namespace ocpp::reqs;
using namespace ocpp::types;

#define ret(x) if (x) return x.value(); else return call;

namespace ocpp {

OcppReqParser::OcppReqParser() {}

reqs::OcppReq OcppReqParser::parse(OcppReqBase<types::OcppActionChargePoint>&& call) {
    switch (call.action) {
    case OcppActionChargePoint::BootNotification: ret(reqs::BootNotification::fromBase(std::move(call)));
    case OcppActionChargePoint::Heartbeat: return call;
    case OcppActionChargePoint::MeterValues: ret(reqs::MeterValues::fromBase(std::move(call)));
    case OcppActionChargePoint::StatusNotification: ret(reqs::StatusNotification::fromBase(std::move(call)));
    ////case OcppActionChargePoint::MeterValues: return onMeterValues(call.payload, conn);
    //// FirmwareStatusNotification can be handled with onStatusNotification
    //case OcppActionChargePoint::FirmwareStatusNotification: return onStatusNotification(call.payload, conn);
    //case OcppActionChargePoint::StartTransaction: return onStartTransaction(call.payload, conn);
    //case OcppActionChargePoint::StopTransaction: return onStopTransaction(call.payload, conn);
    /*case ocpp::OcppActionType::Authorize:
            case ocpp::OcppActionType::StopTransaction:
            */
    default:
        return call;
    }
}

void OcppReqParser::sendGetConfiguration(crow::websocket::connection& conn) {
    OcppReqBase<OcppActionCentralSystem> payload2 {
                                               OcppMessageType::Call,
                                               "ChangeConfiguration " + std::to_string(++_transactionId),
                                               OcppActionCentralSystem::ChangeConfiguration,
                                               {
                                                   { OcppReqPayloadKey::key, "MeterValuesSampledData" },
                                                   { OcppReqPayloadKey::value, "Voltage,Current.Offered,Energy.Active.Import.Register,Power.Active.Import,Power.Offered" }
                                               }};
    conn.send_text(payload2.toBuffer());

    OcppReqBase<OcppActionCentralSystem> payload3 {
                                               OcppMessageType::Call,
                                               "ChangeConfiguration " + std::to_string(++_transactionId),
                                               OcppActionCentralSystem::ChangeConfiguration,
                                               {
                                                   { OcppReqPayloadKey::key, "MeterValuesAlignedData" },
                                                   { OcppReqPayloadKey::value, "Voltage,Current.Offered,Energy.Active.Import.Register,Power.Active.Import,Power.Offered" }
                                               }};
    conn.send_text(payload3.toBuffer());

    OcppReqBase<OcppActionCentralSystem> payload {
                                              OcppMessageType::Call,
                                              "GetConfiguration " + std::to_string(++_transactionId),
                                              OcppActionCentralSystem::GetConfiguration,
                                              {
                                                  { OcppReqPayloadKey::key, "GetConfigurationMaxKeys" }
                                              }};
    conn.send_text(payload.toBuffer());
}

} // namespace ocpp
