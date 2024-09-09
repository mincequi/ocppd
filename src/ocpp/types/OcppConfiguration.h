#pragma once

#include <map>

#include <ocpp/types/OcppConfigurationKey.h>

namespace ocpp::types {

using OcppConfiguration = std::map<OcppConfigurationKey, std::string>;

} // namespace ocpp::types
