#include "OcppMeterValue.h"

#include <ocpp/utils/chrono.h>

namespace ocpp::types {

OcppMeterValue::OcppMeterValue() {}

std::optional<OcppMeterValue> OcppMeterValue::fromJson(const nlohmann::json& json) {
    if (!json.contains("timestamp") ||
        !json.contains("sampledValue") ||
        !json.at("timestamp").is_string() ||
        !json.at("sampledValue").is_array() ||
        json.at("sampledValue").empty()) {
        return std::nullopt;
    }

    OcppMeterValue meterValue;
    meterValue.timestamp = utils::parseIso8601ToEpoch(json.at("timestamp").get<std::string>());
    for (const auto& it : json.at("sampledValue")) {
        auto sampledValue = OcppSampledValue::fromJson(it);
        if (sampledValue.has_value()) {
            meterValue.sampledValues[sampledValue.value().measurand] = sampledValue.value();
        }
    }

    return meterValue;
}

} // namespace ocpp::types
