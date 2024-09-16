#pragma once

#include <ocpp/reqs/OcppReqBase.h>
#include <ocpp/types/OcppActionChargePoint.h>
#include <ocpp/types/OcppChargePointErrorCode.h>
#include <ocpp/types/OcppChargePointStatus.h>

namespace ocpp::reqs {

class StatusNotification : public OcppReqBase<types::OcppActionChargePoint> {
public:
    static std::optional<StatusNotification> fromBase(OcppReqBase<types::OcppActionChargePoint>&& req);

    StatusNotification(OcppReqBase<types::OcppActionChargePoint>&& req, unsigned connectorId, types::OcppChargePointStatus status, types::OcppChargePointErrorCode errorCode);

    const unsigned connectorId;
    const types::OcppChargePointStatus status;
    const types::OcppChargePointErrorCode errorCode;
};

} // namespace ocpp::reqs
