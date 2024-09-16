#pragma once

namespace ocpp::types {

enum class ConfigurationKey {
    // Core Configuration Keys
    AllowOfflineTxForUnknownId,
    AuthorizationCacheEnabled,
    AuthorizeRemoteTxRequests,
    BlinkRepeat,
    ClockAlignedDataInterval,
    ConnectionTimeOut,
    GetConfigurationMaxKeys,
    HeartbeatInterval,
    LightIntensity,
    LocalAuthorizeOffline,
    LocalPreAuthorize,
    MaxEnergyOnInvalidId,
    MeterValuesAlignedData,
    MeterValuesSampledData,
    MeterValueSampleInterval,
    MinimumStatusDuration,
    NumberOfConnectors,
    ResetRetries,
    StopTransactionOnEVSideDisconnect,
    StopTransactionOnInvalidId,
    SupportedFeatureProfiles,
    TransactionMessageAttempts,
    TransactionMessageRetryInterval,
    UnlockConnectorOnEVSideDisconnect,
    WebSocketPingInterval,

    /*
    // Local Authorization List Management
    LocalAuthListEnabled,
    LocalAuthListMaxLength,
    SendLocalListMaxLength,

    // Reservation
    ReserveConnectorZeroSupported,

    // Smart Charging
    ChargeProfileMaxStackLevel,
    ChargingScheduleAllowedChargingRateUnit,
    ChargingScheduleMaxPeriods,
    ConnectorSwitch3to1PhaseSupported,
    MaxChargingProfilesInstalled,

    // Security Extensions (if supported by the implementation)
    CertificateSignedMaxChainSize,
    CertificateSignedMaxCertificateSize,
    MaxCertificatesInstalled,
    SecurityProfile,
    APN,
    APNAuthentication,
    APNUserName,
    APNPassword,
    HeartBeatInterval,
    CentralSystemProtocol,
    APNAuthenticationMethod,

    // Firmware Management
    FirmwareUpdateStatusInterval,
    FirmwareVersion,

    // Diagnostics
    ConnectionTimeout
    */
};

} // namespace ocpp::types
