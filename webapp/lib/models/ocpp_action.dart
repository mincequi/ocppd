enum OcppAction {
  // Firmware Management Profile
  GetDiagnostics,
  UpdateFirmware,

  // Remote Trigger Profile
  TriggerMessage,

  // Reservation Profile
  CancelReservation,
  ReserveNow,

  // Smart Charging Profile
  ClearChargingProfile,
  GetCompositeSchedule,
  SetChargingProfile,

  // Local Authorization List Management Profile
  GetLocalListVersion,
  SendLocalList,

  // Remote Control Profile
  ChangeAvailability,
  ChangeConfiguration,
  ClearCache,
  GetConfiguration,
  RemoteStartTransaction,
  RemoteStopTransaction,
  Reset,
  UnlockConnector
}
