#include "OcppSampledValue.h"

#include <magic_enum.hpp>

namespace ocpp::types {

OcppSampledValue::OcppSampledValue() {}

std::optional<OcppSampledValue> OcppSampledValue::fromJson(const nlohmann::json& json) {
    if (!json.contains("value") ||
        !json["value"].is_string()) {
        // We ignore phase specific values for now
        // json.contains("phase")) {
        return std::nullopt;
    }

    OcppSampledValue sampledValue;
    sampledValue.value = std::stod(json["value"].get<std::string>());
    auto m = measurandFromJson(json);
    if (!m.has_value()) {
        return std::nullopt;
    }

    sampledValue.measurand = m.value();

    if (json.contains("unit") &&
        json["unit"].is_string()) {
        auto str = json["unit"].get<std::string>();
        if (!str.empty() && str[0] == 'k') {
            sampledValue.value *= 1000;
        }
    }

    return sampledValue;
}

std::optional<OcppMeasurand> OcppSampledValue::measurandFromJson(const nlohmann::json& json) {
    if (!json.contains("measurand") ||
        !json["measurand"].is_string()) {
        return std::nullopt;
    }

    std::string phase;
    if (json.contains("phase") &&
        json["phase"].is_string()) {
        phase = json["phase"].get<std::string>();
    }

    auto str = json["measurand"].get<std::string>() + phase;
    str.erase(std::remove(str.begin(), str.end(), '.'), str.end());
    return magic_enum::enum_cast<OcppMeasurand>(str);
}

} // namespace ocpp::types
