#include "ChargePoint.h"

#include <crow/websocket.h>

ChargePoint::ChargePoint(crow::websocket::connection& connection, const std::string& id, const std::string& name)
    : _connection(connection), _id(id) {
    _properties[PropertyKey::name] = name;
}

bool ChargePoint::operator==(const ChargePoint& cp) const {
    return _connection.get_remote_ip() == cp._connection.get_remote_ip();
}

std::string ChargePoint::remoteIp() const {
    return _connection.get_remote_ip();
}

const Properties& ChargePoint::properties() const {
    return _properties;
}

void ChargePoint::setProperties(const Properties& properties) {
    for (const auto& [key, value] : properties) {
        _properties[key] = value;
    }
}
