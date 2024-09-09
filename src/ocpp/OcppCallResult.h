#pragma once

#include <map>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include <ocpp/types/OcppCallResultPayloadKey.h>

namespace ocpp {

struct OcppCallResult {
    using Payload = std::map<types::OcppCallResultPayloadKey, nlohmann::json>;

    const std::string id;
    const Payload payload;
    const void* userData = nullptr;

    static std::optional<OcppCallResult> fromBuffer(const std::string& message);

    std::string toBuffer() const;
};

} // namespace ocpp
