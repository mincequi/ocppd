#pragma once

#include <map>
#include <string>
#include <variant>

#include <ocpp/OcppCallStatus.h>

// Keep this in sync with the flutter app
enum class PropertyKey {
    name,
    status,
    //location,
    power
};

using PropertyValue = std::variant<std::string, ocpp::OcppCallStatus, int>;
using Properties = std::map<PropertyKey, PropertyValue>;
