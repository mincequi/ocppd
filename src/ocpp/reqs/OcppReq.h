#pragma once

#include <variant>

#include <ocpp/reqs/BootNotification.h>
#include <ocpp/reqs/MeterValues.h>
#include <ocpp/reqs/StatusNotification.h>
#include <ocpp/types/OcppActionChargePoint.h>

namespace ocpp::reqs {

using OcppReq = std::variant<OcppReqBase<types::OcppActionChargePoint>,
                             //std::nullopt_t,
                             BootNotification,
                             MeterValues,
                             StatusNotification>;

} // namespace ocpp::reqs
