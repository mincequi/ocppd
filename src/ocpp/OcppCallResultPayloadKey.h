#pragma once

namespace ocpp {

enum class OcppCallResultPayloadKey {
    status,              // e.g., "status" key in a response message
    currentTime,         // e.g., "currentTime" key in BootNotification.conf
    interval,            // e.g., "interval" key in BootNotification.conf
    heartbeatInterval,   // e.g., "heartbeatInterval" key in Heartbeat.conf
    chargingProfile,     // e.g., "chargingProfile" key in SetChargingProfile.conf
    idTagInfo,           // e.g., "idTagInfo" key in Authorize.conf
    expiryDate,          // e.g., "expiryDate" key in Authorize.conf
    parentIdTag,         // e.g., "parentIdTag" key in Authorize.conf
    reservationId,       // e.g., "reservationId" key in ReserveNow.conf
    connectorId,         // e.g., "connectorId" key in ReserveNow.conf
    updateStatus,        // e.g., "updateStatus" key in FirmwareStatusNotification.conf
    chargingProfileStatus, // e.g., "chargingProfileStatus" key in SetChargingProfile.conf
    powerLimit,          // e.g., "powerLimit" key in LoadProfileStatus.conf
    meterStart,          // e.g., "meterStart" key in StartTransaction.conf
    meterStop,           // e.g., "meterStop" key in StopTransaction.conf
    reservationStatus,   // e.g., "reservationStatus" key in ReserveNow.conf
    messageId,           // e.g., "messageId" key in DataTransfer.conf
    data,                // e.g., "data" key in DataTransfer.conf
    firmwareStatus       // e.g., "firmwareStatus" key in FirmwareStatusNotification.conf
};

} // namespace ocpp
