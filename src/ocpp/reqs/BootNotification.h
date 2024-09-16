#pragma once

#include <ocpp/reqs/OcppReqBase.h>
#include <ocpp/types/OcppActionChargePoint.h>

namespace ocpp::reqs {

class BootNotification : public OcppReqBase<types::OcppActionChargePoint> {
public:
    static std::optional<BootNotification> fromBase(OcppReqBase<types::OcppActionChargePoint>&& req);

    BootNotification(OcppReqBase<types::OcppActionChargePoint>&& req,
                     const std::string& chargePointVendor,
                     const std::string& chargePointModel,
                     const std::string& chargePointSerialNumber,
                     const std::string& firmwareVersion);
                     //const std::string& chargeBoxSerialNumber);

    const std::string chargePointVendor;
    const std::string chargePointModel;
    const std::string chargePointSerialNumber;
    const std::string firmwareVersion;
    //const std::string chargeBoxSerialNumber;
};

} // namespace ocpp::reqs
