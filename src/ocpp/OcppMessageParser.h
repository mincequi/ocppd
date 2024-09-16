#pragma once

#include <string>

#include <nlohmann/json_fwd.hpp>

#include <ocpp/Emitter.h>
#include <ocpp/types/OcppActionChargePoint.h>
#include <ocpp/types/OcppMessage.h>

namespace ocpp {

class OcppMessageParser : public Emitter {
public:
    OcppMessageParser();

    types::OcppMessage parse(const std::string& message);

private:
    types::OcppMessage parseCall(nlohmann::json& json);
    std::optional<confs::OcppConfBase> parseCallResult(nlohmann::json& json);
};

} // namespace ocpp
