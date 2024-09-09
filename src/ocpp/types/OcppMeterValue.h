#pragma once

#include <map>
#include <nlohmann/json.hpp>

#include <ocpp/types/OcppMeasurand.h>
#include <ocpp/types/OcppSampledValue.h>

namespace ocpp::types {

class OcppMeterValue {
public:
    OcppMeterValue();

    static std::optional<OcppMeterValue> fromJson(const nlohmann::json& json);

    unsigned int timestamp;
    std::map<OcppMeasurand, OcppSampledValue> sampledValues;
};

} // namespace ocpp::types
