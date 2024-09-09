#pragma once

namespace ocpp {

class OcppWebSocketService {
public:
    virtual void sendCall() = 0;

};

} // namespace ocpp
