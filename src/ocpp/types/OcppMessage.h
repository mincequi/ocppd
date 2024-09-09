#pragma once

#include <variant>

#include <ocpp/OcppCall.h>
#include <ocpp/OcppCallResult.h>
#include <ocpp/calls/OcppMeterValues.h>
#include <ocpp/types/OcppActionChargePoint.h>

namespace ocpp::types {

using OcppMessage = std::variant<OcppCall<types::OcppActionChargePoint>,
                                 OcppCallResult,
                                 calls::OcppMeterValues,
                                 std::nullopt_t>;

}
