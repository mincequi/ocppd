#pragma once

#include <map>
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

    template <typename T>
    void send(const std::map<std::string, T>&,
              crow::websocket::connection* conn = nullptr);

private:
    std::mutex _mutex;
    std::unordered_set<crow::websocket::connection*> _clients;
};
