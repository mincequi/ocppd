#pragma once

#include <mutex>
#include <unordered_set>

#include "ChargePoint.h"

namespace crow::websocket {
class connection;
} // namespace crow::websocket

class ApiClientRepository {
public:
    ApiClientRepository();

    void add(crow::websocket::connection* conn);
    void remove(crow::websocket::connection* conn);

    void broadcast(const ChargePoints& chargePoints);

private:
    std::mutex _mutex;
    std::unordered_set<crow::websocket::connection*> _clients;
};
