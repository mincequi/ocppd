#pragma once

#include <map>

#include <ocpp/WebSocketConnection.h>
#include <ocpp/types/ConfigurationKeys.h>

#include "Properties.h"

namespace crow::websocket {
class connection;
} // namespace crow::websocket

using namespace ocpp;
using namespace ocpp::types;

class ChargePoint : public WebSocketConnection {
public:
    ChargePoint(crow::websocket::connection* connection, const std::string& id, const std::string& name);

private:
    virtual void send(const std::string& message) override;

    friend class ChargePointRepository;
    friend class OcppRoute;

    // comparison operator
    bool operator==(const ChargePoint& cp) const;

    std::string remoteIp() const;

    // properties
    const Properties& properties() const;
    void setProperties(const Properties& properties);
    Properties _properties;

    // configuration
    const ConfigurationKeys& configuration() const;
    void setConfiguration(const ConfigurationKeys& configuration);
    ConfigurationKeys _configuration;

    void sendPowerOffered(int powerOffered);

    crow::websocket::connection* _connection;
    const std::string _id;
};
