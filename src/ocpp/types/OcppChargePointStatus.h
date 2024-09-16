#pragma once

namespace ocpp::types {

enum class OcppChargePointStatus {
    Available,
    Preparing,
    Charging,
    SuspendedEV,
    SuspendedEVSE,
    Finishing,
    Reserved,
    Unavailable
};

} // namespace ocpp::types
