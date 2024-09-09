#pragma once

#include <map>
#include <nlohmann/json.hpp>

#include <ocpp/types/OcppCallPayloadKey.h>

namespace ocpp::types {

using OcppCallPayload = std::map<OcppCallPayloadKey, nlohmann::json>;

} // namespace ocpp::types
