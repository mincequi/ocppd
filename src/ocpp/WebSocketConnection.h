#pragma once

#include <string>

namespace ocpp {

class WebSocketConnection {
public:
    virtual void send(const std::string& message) = 0;
};

} // namespace ocpp
