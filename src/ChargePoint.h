#pragma once

#include <map>

#include <ocpp/types/OcppConfiguration.h>

#include "Properties.h"

namespace crow::websocket {
class connection;
} // namespace crow::websocket

using namespace ocpp::types;

// TODO: make this a pure data class. It should not have a connection, but only
// user data instead (actual the connection). Connection should be handled by
// the repository.
class ChargePoint {
public:
    ChargePoint(crow::websocket::connection* connection, const std::string& id, const std::string& name);

private:
    friend class ChargePointRepository;

    // comparison operator
    bool operator==(const ChargePoint& cp) const;

    std::string remoteIp() const;

    // properties
    const Properties& properties() const;
    void setProperties(const Properties& properties);
    Properties _properties;

    // configuration
    const OcppConfiguration& configuration() const;
    void setConfiguration(const OcppConfiguration& configuration);
    OcppConfiguration _configuration;

    void sendPowerOffered(int powerOffered);

    crow::websocket::connection* _connection;
    const std::string _id;
};

using ChargePoints = std::map<std::string, Properties>;
