#pragma once

namespace ocpp {

enum class OcppCallPayloadKey {
    // BootNotification
    chargePointVendor,
    chargePointModel,
    chargePointSerialNumber,
    chargeBoxSerialNumber,
    firmwareVersion,
    iccid,
    imsi,
    meterType,
    meterSerialNumber,

    // Authorize
    idTag,

    // StartTransaction
    connectorId,
    idTagStart,
    meterStart,
    reservationId,
    timestamp,

    // StopTransaction
    idTagStop,
    meterStop,
    transactionId,
    //timestamp,
    reason,
    transactionData,

    // Heartbeat
    // No specific payload keys for Heartbeat

    // StatusNotification
    //connectorId,
    errorCode,
    info,
    status,
    //timestamp,
    vendorId,
    vendorErrorCode,

    // MeterValues
    //connectorId,
    transactionIdMeter,
    meterValue,

    // RemoteStartTransaction
    //connectorId,
    idTagRemoteStart,
    chargingProfile,

    // RemoteStopTransaction
    transactionIdRemoteStop,

    // Reset
    type,

    // UnlockConnector
    //connectorId,

    // FirmwareStatusNotification
    statusFirmware,

    // DiagnosticsStatusNotification
    statusDiagnostics,

    // DataTransfer
    vendorIdData,
    messageId,
    data,

    // ReserveNow
    //connectorId,
    expiryDate,
    idTagReserve,
    parentIdTag,
    reservationIdReserve,

    // CancelReservation
    reservationIdCancel,

    // SendLocalList
    listVersion,
    localAuthorizationList,
    updateType,

    // GetLocalListVersion
    // No specific payload keys for GetLocalListVersion

    // UpdateFirmware
    location,
    retries,
    retrieveDate,
    retryInterval,

    // GetDiagnostics
    locationDiagnostics,
    startTime,
    stopTime,
    retriesDiagnostics,
    retryIntervalDiagnostics,

    // ChangeConfiguration
    key,
    value,

    // GetConfiguration
    keyGetConfig,

    // ClearCache
    // No specific payload keys for ClearCache

    // ChangeAvailability
    //connectorId,
    typeChangeAvailability,

    // TriggerMessage
    requestedMessage,

    // CertificateSigned
    certificateChain,
    certificateType,

    // InstallCertificate
    certificateTypeInstall,
    certificateInstall,

    // DeleteCertificate
    certificateTypeDelete,

    // SignedFirmwareStatusNotification
    statusSignedFirmware,

    // SignCertificate
    CSR,
    certificateTypeSign
};

} // namespace ocpp
