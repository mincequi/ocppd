#pragma once

#include <map>
#include <optional>
#include <string>
#include <variant>

#include <ocpp/OcppCall.h>
#include <ocpp/OcppCallResultPayloadKey.h>

namespace ocpp {

struct OcppCallResult {
    using Payload = std::map<OcppCallResultPayloadKey, std::variant<std::string, int>>;

    const std::string id;
    const Payload payload;

    static std::optional<OcppCallResult> fromBuffer(const std::string& message);

    std::string toBuffer() const;
};

} // namespace ocpp
