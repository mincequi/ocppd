#include "OcppChargingProfile.h"

namespace ocpp::types {

using json = nlohmann::json;

nlohmann::json OcppChargingProfile::toJson() const {
    return json {
        {"chargingProfileId", 1},
        {"transactionId", 12345},
        {"stackLevel", 0},
        {"chargingProfilePurpose", "TxProfile"},
        {"chargingProfileKind", "Absolute"},
        {"chargingSchedule", {
            {"chargingRateUnit", "A"},
            {"chargingSchedulePeriod", {
                {
                    {"startPeriod", 0},
                    {"limit", limit},
                    {"numberPhases", numberPhases}
                }
            }}
        }}
    };
}

} // namespace ocpp::types
