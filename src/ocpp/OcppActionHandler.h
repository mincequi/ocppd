#pragma once

namespace ocpp {

class OcppCall;

class OcppActionHandler {
public:
    virtual bool onCall(const OcppCall& call, void* userData = nullptr) = 0;
};

} // namespace ocpp
