// Keep this in sync with the server-side enum
enum OcppChargePointStatus {
  // For StatusNotification
  Available, // The connector is available for use
  Occupied, // The connector is currently in use
  Faulted, // The connector has a fault
  Unavailable, // The connector is not available for use
  Reserved, // The connector is reserved
  Finishing, // The connector is finishing a transaction
  Charging, // The connector is actively charging a vehicle
  SuspendedEV, // The EV has requested to pause charging (e.g., EV is not drawing power)
  SuspendedEVSE, // The EVSE (charge point) has paused charging (e.g., due to external conditions)

  // For DiagnosticsStatusNotification
  Uploading, // DiagnosticsStatusNotification: Diagnostics data is being uploaded
  Uploaded, // DiagnosticsStatusNotification: Diagnostics data has been uploaded
  UploadFailed, // DiagnosticsStatusNotification: Diagnostics data upload failed

  // For FirmwareStatusNotification
  Downloading, // FirmwareStatusNotification: Firmware is being downloaded
  Downloaded, // FirmwareStatusNotification: Firmware download completed
  Installing, // FirmwareStatusNotification: Firmware is being installed
  Installed, // FirmwareStatusNotification: Firmware installation completed
  InstallFailed // FirmwareStatusNotification: Firmware installation failed
}
