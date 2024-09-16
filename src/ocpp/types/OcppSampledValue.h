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

private:
    static std::optional<OcppMeasurand> measurandFromJson(const nlohmann::json& json);

};

} // namespace ocpp::types
