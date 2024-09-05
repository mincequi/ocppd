#pragma once

#include "Properties.h"

namespace crow::websocket {
class connection;
} // namespace crow::websocket

class ChargePoint {
public:
    ChargePoint(crow::websocket::connection& connection, const std::string& id, const std::string& name);

private:
    friend class ChargePointRepository;

    // comparison operator
    bool operator==(const ChargePoint& cp) const;

    std::string remoteIp() const;

    const Properties& properties() const;
    void setProperties(const Properties& properties);

    crow::websocket::connection& _connection;
    const std::string _id;

    Properties _properties;
};

using ChargePoints = std::map<std::string, Properties>;
