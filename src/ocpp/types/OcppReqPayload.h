#pragma once

#include <map>
#include <nlohmann/json.hpp>

#include <ocpp/types/OcppReqPayloadKey.h>

namespace ocpp::types {

using OcppReqPayload = std::map<OcppReqPayloadKey, nlohmann::json>;

} // namespace ocpp::types
