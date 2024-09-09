#pragma once

#include <string>

#include <ocpp/types/OcppMessageType.h>
#include <ocpp/types/OcppCallPayload.h>

namespace ocpp {

template<typename T>
class OcppCall {
public:
    const types::OcppMessageType type;
    const std::string id;
    const T action;
    const types::OcppCallPayload payload;

    std::string toBuffer() const;
};

} // namespace ocpp
