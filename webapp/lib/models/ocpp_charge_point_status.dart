// Keep this in sync with the server-side enum
enum OcppChargePointStatus {
  Available,
  Preparing,
  Charging,
  SuspendedEV,
  SuspendedEVSE,
  Finishing,
  Reserved,
  Unavailable,
  Faulted,
}
