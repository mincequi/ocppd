#include "OcppSampledValue.h"

#include <magic_enum.hpp>

namespace ocpp::types {

OcppSampledValue::OcppSampledValue() {}

std::optional<OcppSampledValue> OcppSampledValue::fromJson(const nlohmann::json& json) {
    if (!json.contains("value") ||
        !json["value"].is_string() ||
        // We ignore phase specific values for now
        json.contains("phase")) {
        return std::nullopt;
    }

    OcppSampledValue sampledValue;
    sampledValue.value = std::stod(json["value"].get<std::string>());
    if (json.contains("measurand") &&
        json["measurand"].is_string()) {
        auto str = json["measurand"].get<std::string>();
        str.erase(std::remove(str.begin(), str.end(), '.'), str.end());
        auto m = magic_enum::enum_cast<OcppMeasurand>(str);
        if (m.has_value()) {
            sampledValue.measurand = m.value();
        }
    }

    if (json.contains("unit") &&
        json["unit"].is_string()) {
        auto str = json["unit"].get<std::string>();
        if (!str.empty() && str[0] == 'k') {
            sampledValue.value *= 1000;
        }
    }

    return sampledValue;
}

} // namespace ocpp::types
