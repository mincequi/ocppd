#include "ChangeConfiguration.h"

#include <string>

#include <magic_enum.hpp>

using namespace ocpp::reqs;
using namespace ocpp::types;

std::vector<std::string> serialize(const ChangeConfiguration::Value& value) {
    std::vector<std::string> result;
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::vector<OcppMeasurand>>) {
            for (const auto& measurand : arg) {
                std::string str = std::string(magic_enum::enum_name(measurand));
                //Convert CamelCase to separate by a dot
                for (size_t i = 1; i < str.size(); i++) {
                    if (isupper(str[i])) {
                        str.insert(i++, 1, '.');
                    }
                }
                result.push_back(str);
            }
            return result;
        }
    }, value);
    return result;
}

ChangeConfiguration::ChangeConfiguration(types::OcppConfigurationKey key, Value value)
    : OcppReqBase{ "", types::OcppActionCentralSystem::ChangeConfiguration,
                  {{ types::OcppReqPayloadKey::key, magic_enum::enum_name(key) },
                   { types::OcppReqPayloadKey::value, serialize(value) }} } {
}
