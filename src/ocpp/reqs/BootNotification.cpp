#include "BootNotification.h"

namespace ocpp::reqs {

using namespace types;

std::optional<BootNotification> BootNotification::fromBase(OcppReqBase<types::OcppActionChargePoint>&& req) {
    if (req.action != types::OcppActionChargePoint::BootNotification ||
        !req.payload.contains(OcppReqPayloadKey::chargePointVendor) ||
        !req.payload.contains(OcppReqPayloadKey::chargePointModel) ||
        !req.payload.contains(OcppReqPayloadKey::chargePointSerialNumber) ||
        //!req.payload.contains(OcppReqPayloadKey::chargeBoxSerialNumber) ||
        !req.payload.contains(OcppReqPayloadKey::firmwareVersion)
        //!req.payload.contains(OcppReqPayloadKey::iccid) ||
        //!req.payload.contains(OcppReqPayloadKey::imsi) ||
        //!req.payload.contains(OcppReqPayloadKey::meterType) ||
        //!req.payload.contains(OcppReqPayloadKey::meterSerialNumber)
        ) {
        return std::nullopt;
    }

    return BootNotification(std::move(req),
                            req.payload.at(OcppReqPayloadKey::chargePointVendor),
                            req.payload.at(OcppReqPayloadKey::chargePointModel),
                            req.payload.at(OcppReqPayloadKey::chargePointSerialNumber),
                            req.payload.at(OcppReqPayloadKey::firmwareVersion));
}

BootNotification::BootNotification(OcppReqBase<types::OcppActionChargePoint>&& req,
                                   const std::string& chargePointVendor,
                                   const std::string& chargePointModel,
                                   const std::string& chargePointSerialNumber,
                                   const std::string& firmwareVersion) :
    OcppReqBase(std::move(req)),
    chargePointVendor(chargePointVendor),
    chargePointModel(chargePointModel),
    chargePointSerialNumber(chargePointSerialNumber),
    firmwareVersion(firmwareVersion) {
}

} // namespace ocpp::reqs
