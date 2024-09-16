#include "StatusNotification.h"

#include <magic_enum.hpp>

namespace ocpp::reqs {

using namespace ocpp::types;

std::optional<StatusNotification> StatusNotification::fromBase(OcppReqBase<types::OcppActionChargePoint>&& req) {
    if (!req.payload.contains(OcppReqPayloadKey::connectorId) ||
        !req.payload.contains(OcppReqPayloadKey::status) ||
        !req.payload.contains(OcppReqPayloadKey::errorCode)) {
        return std::nullopt;
    }

    auto status = magic_enum::enum_cast<OcppChargePointStatus>(req.payload.at(OcppReqPayloadKey::status).get<std::string>());
    if (!status.has_value()) {
        return std::nullopt;
    }

    auto errorCode = magic_enum::enum_cast<OcppChargePointErrorCode>(req.payload.at(OcppReqPayloadKey::errorCode).get<std::string>());
    if (!errorCode.has_value()) {
        return std::nullopt;
    }

    return StatusNotification(std::move(req),
                              req.payload.at(OcppReqPayloadKey::connectorId),
                              status.value(),
                              errorCode.value());
}

StatusNotification::StatusNotification(OcppReqBase<types::OcppActionChargePoint>&& req, unsigned connectorId, types::OcppChargePointStatus status, types::OcppChargePointErrorCode errorCode)
    : OcppReqBase(std::move(req)), connectorId(connectorId), status(status), errorCode(errorCode) {
}

} // namespace ocpp::reqs
