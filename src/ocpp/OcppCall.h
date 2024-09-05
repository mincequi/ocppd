#pragma once

#include <any>
#include <map>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include <ocpp/OcppActionType.h>
#include <ocpp/OcppCallPayloadKey.h>
#include <ocpp/OcppCallStatus.h>
#include <ocpp/OcppMessageType.h>

namespace ocpp {

struct OcppCall {
    using Payload = std::map<OcppCallPayloadKey, nlohmann::json>;

    const OcppMessageType type;
    const std::string id;
    const OcppActionType action;
    const Payload payload;

    std::string toBuffer() const;
};

} // namespace ocpp
