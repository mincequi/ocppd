#pragma once

#include <variant>

#include <ocpp/confs/OcppConfBase.h>
#include <ocpp/reqs/OcppReqBase.h>
#include <ocpp/types/OcppActionChargePoint.h>

namespace ocpp::types {

using OcppMessage = std::variant<reqs::OcppReqBase<types::OcppActionChargePoint>,
                                 confs::OcppConfBase,
                                 std::nullopt_t>;

}
