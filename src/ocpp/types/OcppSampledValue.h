#pragma once

#include <optional>
#include <nlohmann/json.hpp>

#include <ocpp/types/OcppMeasurand.h>

namespace ocpp::types {

class OcppSampledValue {
public:
    OcppSampledValue();

    static std::optional<OcppSampledValue> fromJson(const nlohmann::json& json);

    double value;
    OcppMeasurand measurand = OcppMeasurand::EnergyActiveImportRegister;
};

} // namespace ocpp::types
