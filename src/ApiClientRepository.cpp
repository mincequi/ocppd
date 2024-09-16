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
    conn->close();
    _clients.erase(conn);
}

template <typename T>
void ApiClientRepository::send(const std::map<std::string, T>& cps, crow::websocket::connection* conn) {
    std::lock_guard<std::mutex> _(_mutex);

    // Encode to CBOR
    json j;
    for (const auto& cp : cps) {
        for (const auto& kv : cp.second) {
            if constexpr (std::is_same_v<T, Properties>) {
                std::visit([&](auto&& arg) {
                    using U = std::decay_t<decltype(arg)>;
                    j[cp.first]["properties"][std::to_string(magic_enum::enum_integer(kv.first))] = arg;
                }, kv.second);
            } else if constexpr (std::is_same_v<T, ConfigurationKeys>) {
                std::visit([&](auto&& arg) {
                    using U = std::decay_t<decltype(arg)>;
                    j[cp.first]["configuration"][std::to_string(magic_enum::enum_integer(kv.first))] = arg;
                }, kv.second);
            }
        }
    }

    const auto data = json::to_cbor(j);
    if (conn) {
        conn->send_binary({data.begin(), data.end()});
        return;
    }
    for (auto client : _clients) {
        client->send_binary({data.begin(), data.end()});
    }
}

// explicit instantiation
template void ApiClientRepository::send<Properties>(const std::map<std::string, Properties>&, crow::websocket::connection*);
template void ApiClientRepository::send<ConfigurationKeys>(const std::map<std::string, ConfigurationKeys>&, crow::websocket::connection*);
