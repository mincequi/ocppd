#pragma once

#include <ocpp/OcppCall.h>
#include <ocpp/types/OcppMessage.h>

namespace ocpp {

class OcppCallHandler {
public:
    virtual bool onCall(void* userData, const types::OcppMessage& call) = 0;
};

} // namespace ocpp
