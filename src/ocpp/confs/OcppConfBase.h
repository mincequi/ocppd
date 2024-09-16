#pragma once

#include <map>
#include <string>

#include <nlohmann/json.hpp>

#include <ocpp/types/OcppConfPayloadKey.h>

namespace ocpp::confs {

struct OcppConfBase {
    using Payload = std::map<types::OcppConfPayloadKey, nlohmann::json>;

    const std::string id;
    const Payload payload;

    std::string toBuffer() const;
};

} // namespace ocpp::confs
