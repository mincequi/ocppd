#include "ApiClientRepository.h"

#include <magic_enum.hpp>
#include <crow/websocket.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ApiClientRepository::ApiClientRepository() {}

void ApiClientRepository::add(crow::websocket::connection* conn) {
    std::lock_guard<std::mutex> _(_mutex);
    _clients.insert(conn);
}

void ApiClientRepository::remove(crow::websocket::connection* conn) {
    std::lock_guard<std::mutex> _(_mutex);
    _clients.erase(conn);
}

void ApiClientRepository::broadcast(const ChargePoints& chargePoints) {
    std::lock_guard<std::mutex> _(_mutex);

    // Encode to CBOR
    json j;
    for (const auto& cp : chargePoints) {
        for (const auto& prop : cp.second) {
            std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                j[cp.first][std::to_string(magic_enum::enum_integer(prop.first))] = arg;
            }, prop.second);
        }
    }

    const auto data = json::to_cbor(j);
    for (auto client : _clients) {
        client->send_binary({data.begin(), data.end()});
    }
}
