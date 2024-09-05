#include "OcppRoute.h"

#include "ChargePointRepository.h"

using namespace ocpp;

OcppRoute::OcppRoute(crow::SimpleApp& app,
                     ChargePointRepository& chargePoints)
    : _app(app),
      _chargePoints(chargePoints),
      _handler(_chargePoints) {
    CROW_WEBSOCKET_ROUTE(app, "/ocpp")
        .onopen([&](crow::websocket::connection& conn) {
            CROW_LOG_INFO<< "ocpp> " << conn.get_remote_ip() << "> new client";
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason) {
            CROW_LOG_INFO<< "ocpp> " << conn.get_remote_ip() << "> client closed: " << reason;
            _chargePoints.removeByIp(conn);
        })
        .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
            if (is_binary) {
                CROW_LOG_WARNING<< "ocpp> " << conn.get_remote_ip() << "> unexpected binary message";
                return;
            }

            auto msg = _parser.parse(data);
            if (std::holds_alternative<std::nullopt_t>(msg)) {
                CROW_LOG_WARNING<< "ocpp> " << conn.get_remote_ip() << "> invalid message: " << data;
                return;
            }

            std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, OcppCall>) {
                    CROW_LOG_INFO<< "ocpp> " << conn.get_remote_ip() << "> received call: " << data;
                    if (!_handler.onCall(arg, &conn)) {
                        CROW_LOG_WARNING<< "ocpp> " << conn.get_remote_ip() << "> unhandled call: " << data;
                        return;
                    }
                    auto result = _generator.generate(arg).toBuffer();
                    CROW_LOG_INFO<< "ocpp> " << conn.get_remote_ip() << "> sending call result: " << result;
                    conn.send_text(result);
                } else if constexpr (std::is_same_v<T, OcppCallResult>) {
                    CROW_LOG_INFO<< "ocpp> " << conn.get_remote_ip() << "> received call result: " << data;
                }
            }, msg);
        })
        .onerror([](crow::websocket::connection& conn, const std::string& data) {
            CROW_LOG_ERROR<< "ocpp> " << conn.get_remote_ip() << "> error: " << data;
        });
}
