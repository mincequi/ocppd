#pragma once

#include <map>

#include <ocpp/types/ConfigurationKey.h>
#include <ocpp/types/ConfigurationValue.h>

namespace ocpp::types {

using ConfigurationKeys = std::map<ConfigurationKey, ConfigurationValue>;

} // namespace ocpp::types
