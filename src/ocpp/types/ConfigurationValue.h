#pragma once

#include <variant>

#include <ocpp/types/OcppMeasurand.h>

namespace ocpp::types {

using ConfigurationValue = std::variant<bool, int, std::string, std::vector<OcppMeasurand>>;

} // namespace ocpp::types
