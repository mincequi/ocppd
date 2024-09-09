#pragma once

namespace ocpp::types {

enum class OcppMessageType {
    Call = 2,
    CallResult = 3,
    CallError = 4
};

} // namespace ocpp::types
