#pragma once

namespace ocpp::types {

enum class OcppActionChargePoint {
    Authorize,
    BootNotification,
    DataTransfer,
    DiagnosticsStatusNotification,
    FirmwareStatusNotification,
    Heartbeat,
    MeterValues,
    StartTransaction,
    StatusNotification,
    StopTransaction,
};

} // namespace ocpp::types

