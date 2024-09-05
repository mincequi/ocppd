#pragma once

namespace ocpp {

enum class OcppCallResultStatus {
    // Common status values
    Accepted,               // General acceptance
    Rejected,               // General rejection
    Pending,                // Request is pending (e.g., BootNotification)

    // Specific status values
    Faulted,                // Reservation or transaction fault
    Occupied,               // Connector is occupied (e.g., ReserveNow)
    Unavailable,            // Connector or service is unavailable (e.g., ReserveNow)
    NotSupported,           // Operation not supported (e.g., ChargingProfile)
    VersionMismatch,        // Version mismatch in firmware update

    // Firmware and update-related values
    Downloaded,             // Firmware downloaded
    DownloadFailed,         // Firmware download failed
    InstallationFailed,     // Firmware installation failed
    Installed,              // Firmware installed successfully
    Failed,                 // General failure (e.g., Update)

    // IdTag-related values
    Blocked,                // IdTag is blocked
    Expired,                // IdTag is expired
    Invalid,                // IdTag is invalid
    ConcurrentTx            // IdTag is already used in another transaction
};

} // namespace ocpp
