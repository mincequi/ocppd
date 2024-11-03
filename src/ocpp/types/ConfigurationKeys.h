#pragma once

#include <map>

#include <ocpp/types/OcppConfigurationKey.h>
#include <ocpp/types/ConfigurationValue.h>

namespace ocpp::types {

using ConfigurationKeys = std::map<OcppConfigurationKey, ConfigurationValue>;

} // namespace ocpp::types
