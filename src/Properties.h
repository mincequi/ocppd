#pragma once

#include <map>
#include <string>
#include <variant>

#include <ocpp/types/OcppChargePointErrorCode.h>
#include <ocpp/types/OcppChargePointStatus.h>

// Keep this in sync with the flutter app
enum class PropertyKey {
    name,
    status,
    errorCode,
    location,
    power,
    powerOffered,
    energy,
    current,
    voltage,
    temperature,
    humidity,
    lastUpdated,
};

using PropertyValue = std::variant<std::string,
                                   ocpp::types::OcppChargePointStatus,
                                   ocpp::types::OcppChargePointErrorCode,
                                   int>;
using Properties = std::map<PropertyKey, PropertyValue>;
