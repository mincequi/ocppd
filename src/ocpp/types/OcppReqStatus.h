#pragma once

namespace ocpp::types {

enum class OcppReqStatus {
    // For StatusNotification
    Available,      // The charge point is available for a new session.
    Preparing,      // The charge point is preparing to start a session.
    Charging,       // The charge point is currently charging.
    SuspendedEV,    // Charging is suspended due to EV (e.g., EV paused charging).
    SuspendedEVSE,  // Charging is suspended by the charge point.
    Finishing,      // Charging session is finishing up.
    Reserved,       // The charge point is reserved for a specific EV.
    Unavailable,    // The charge point is not available (e.g., due to an error).
    Faulted,        // The charge point has a fault.

    // For DiagnosticsStatusNotification
    Idle,           // DiagnosticsStatusNotification: No diagnostics data is being uploaded
    Uploading,      // DiagnosticsStatusNotification: Diagnostics data is being uploaded
    Uploaded,       // DiagnosticsStatusNotification: Diagnostics data has been uploaded
    UploadFailed,   // DiagnosticsStatusNotification: Diagnostics data upload failed

    // For FirmwareStatusNotification
    Downloading,    // FirmwareStatusNotification: Firmware is being downloaded
    Downloaded,     // FirmwareStatusNotification: Firmware download completed
    DownloadFailed, // FirmwareStatusNotification: Firmware download failed
    Installing,     // FirmwareStatusNotification: Firmware is being installed
    Installed,      // FirmwareStatusNotification: Firmware installation completed
    InstallationFailed,  // FirmwareStatusNotification: Firmware installation failed
};

} // namespace ocpp::types
