#pragma once

namespace ocpp::types {

enum class OcppCallResultPayloadKey {
    // BootNotification
    currentTime,  // Also used in Heartbeat
    interval,
    status,  // Common in multiple messages

    // Authorize
    idTagInfo,  // Also used in StartTransaction, StopTransaction
    expiryDate,  // Also used in StartTransaction
    parentIdTag,  // Also used in StartTransaction

    // StartTransaction
    transactionId,
    // idTagInfo,  // Already defined above
    // expiryDate,  // Already defined above
    // parentIdTag,  // Already defined above

    // StopTransaction
    // idTagInfo,  // Already defined above
    meterStop,
    timestamp,  // Also used in StatusNotification
    reason,
    transactionData,

    // StatusNotification
    connectorId,  // Also used in MeterValues
    // status,  // Already defined above
    errorCode,
    info,
    // timestamp,  // Already defined above
    vendorId,  // Also used in DataTransfer
    vendorErrorCode,

    // Heartbeat
    // currentTime,  // Already defined above

    // MeterValues
    // connectorId,  // Already defined above
    // transactionId,  // Already defined above
    meterValue,

    // DiagnosticsStatusNotification
    // status,  // Already defined above

    // FirmwareStatusNotification
    // status,  // Already defined above

    // DataTransfer
    data,
    // status,  // Already defined above
    // vendorId,  // Already defined above

    // ChangeConfiguration
    // status,  // Already defined above

    // RemoteStartTransaction
    // status,  // Already defined above

    // RemoteStopTransaction
    // status,  // Already defined above

    // UnlockConnector
    // status,  // Already defined above

    // GetConfiguration
    configurationKey,
    unknownKey,

    // ChangeAvailability
    // status,  // Already defined above

    // Reset
    // status,  // Already defined above

    // SendLocalList
    // status,  // Already defined above
    hash,

    // GetLocalListVersion
    listVersion,

    // ReserveNow
    // status,  // Already defined above

    // CancelReservation
    // status,  // Already defined above

    // ClearCache
    // status  // Already defined above
};

} // namespace ocpp::types
