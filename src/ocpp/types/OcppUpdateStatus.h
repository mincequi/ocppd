#pragma once

namespace ocpp::types {

enum class OcppUpdateStatus {
    Accepted,
    Failed,
    NotSupported,
    VersionMismatch
};

} // namespace ocpp::types
