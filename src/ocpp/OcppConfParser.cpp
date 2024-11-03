#include "OcppConfParser.h"

#include <sstream>

#include <magic_enum.hpp>

#include <ocpp/confs/OcppConfStatus.h>
#include <ocpp/types/ConfigurationKeys.h>

using namespace ocpp::confs;
using namespace ocpp::types;

namespace ocpp {

OcppConfParser::OcppConfParser() {
    _handlers[types::OcppConfPayloadKey::configurationKey] = [this](const nlohmann::json& value) {
        ConfigurationKeys configuration;
        for (const auto& item : value) {
            if (!item.is_object() ||
                !item.contains("key") ||
                !item.contains("value") ||
                !item.contains("readonly") ||
                !item["key"].is_string() ||
                !item["value"].is_string() ||
                !item["readonly"].is_boolean() ||
                item["readonly"].get<bool>()) {
                continue;
            }

            const auto key = magic_enum::enum_cast<OcppConfigurationKey>(item["key"].get<std::string>());
            if (!key.has_value()) {
                continue;
            }

            switch (key.value()) {
            case OcppConfigurationKey::MeterValuesAlignedData:
            case OcppConfigurationKey::MeterValuesSampledData:
                configuration[key.value()] = parseMeasurands(item["value"].get<std::string>());
                break;
            default: {
                const auto value = item["value"].get<std::string>();
                if (value == "false") {
                    configuration[key.value()] = false;
                } else if (value == "true") {
                    configuration[key.value()] = true;
                } else {
                    int i = std::numeric_limits<int>::min();
                    std::stringstream ss;
                    ss << value;
                    ss >> i;

                    if (i != std::numeric_limits<int>::min()) {
                        configuration[key.value()] = i;
                    } else {
                        configuration[key.value()] = value;
                    }
                }
                break;
            }
            }
        }
        return configuration;
    };

    _handlers[types::OcppConfPayloadKey::status] = [this](const nlohmann::json& value) -> OcppConfField {
        const auto status = magic_enum::enum_cast<OcppConfStatus>(value.get<std::string>());
        if (!status.has_value()) {
            return std::nullopt;
        }

        return status.value();
    };
}

confs::OcppConfField OcppConfParser::parse(types::OcppConfPayloadKey key, const nlohmann::json& value) {
    if (!_handlers.contains(key)) {
        return std::nullopt;
    }

    return _handlers[key](value);
}

std::vector<types::OcppMeasurand> OcppConfParser::parseMeasurands(const std::string& value) {
    // value is a comma separated list of measurands
    std::vector<types::OcppMeasurand> measurands;
    std::istringstream ss(value);
    std::string item;
    while (std::getline(ss, item, ',')) {
        item.erase(std::remove(item.begin(), item.end(), '.'), item.end());
        const auto measurand = magic_enum::enum_cast<types::OcppMeasurand>(item);
        if (measurand.has_value()) {
            measurands.push_back(measurand.value());
        }
    }
    return measurands;
}

} // namespace ocpp
