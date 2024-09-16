#pragma once

namespace ocpp::types {

// From Charge Point to Central System, we only need status and configurationKey
enum class OcppConfPayloadKey {
    // Authorize.conf
    idTagInfo,

    // BootNotification.conf
    currentTime,
    interval,
    status,

    // DataTransfer.conf
    data,
    //status, // Duplicate for other response types

    // GetConfiguration
    configurationKey,
    unknownKey,

    // StartTransaction.conf
    //idTagInfo,
    transactionId,
};

} // namespace ocpp::types
