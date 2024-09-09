#pragma once

#include <map>
#include <string>
#include <variant>

#include <ocpp/types/OcppCallStatus.h>

// Keep this in sync with the flutter app
enum class PropertyKey {
    name,
    status,
    //location,
    power,
    powerOffered
};

using PropertyValue = std::variant<std::string, ocpp::types::OcppCallStatus, int>;
using Properties = std::map<PropertyKey, PropertyValue>;
