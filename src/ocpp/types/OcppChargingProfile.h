#pragma once

#include <nlohmann/json.hpp>

namespace ocpp::types {

class OcppChargingProfile {
public:
    int numberPhases = 3;
    double limit = 32.0;

    nlohmann::json toJson() const;
};

} // namespace ocpp::types
