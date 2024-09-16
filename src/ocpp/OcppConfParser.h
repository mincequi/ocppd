#pragma once

#include <ocpp/confs/OcppConfBase.h>
#include <ocpp/confs/OcppConfField.h>
#include <ocpp/types/OcppConfPayloadKey.h>

namespace ocpp {

class OcppConfParser {
public:
    OcppConfParser();

    confs::OcppConfField parse(types::OcppConfPayloadKey key, const nlohmann::json& value);

private:
    std::vector<types::OcppMeasurand> parseMeasurands(const std::string& value);

    using Handler = std::function<confs::OcppConfField(const nlohmann::json& value)>;
    std::map<types::OcppConfPayloadKey, Handler> _handlers;
};

} // namespace ocpp
