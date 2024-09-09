#include "OcppRoute.h"

#include <magic_enum.hpp>

#include "ChargePointRepository.h"

#include "utils/Overload.h"
#include "utils/log.h"

using namespace ocpp;

OcppRoute::OcppRoute(crow::SimpleApp& app,
                     ChargePointRepository& chargePoints) :
    _app(app),
    _chargePoints(chargePoints),
    _callHandler(_chargePoints),
    _callResultHandler(_chargePoints) {
    CROW_WEBSOCKET_ROUTE(app, "/ocpp")
        .onopen([&](crow::websocket::connection& conn) {
            info << conn.get_remote_ip() << "> new client";
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
            info << "> client closed: " << reason;
            _chargePoints.removeByIp(&conn);
        })
        .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
            if (is_binary) {
                warning << conn.get_remote_ip() << "> unexpected binary message";
                return;
            }

            auto msg = _parser.parse(data);
            std::visit(utils::Overload {
                [&](const std::nullopt_t&) {
                    warning << conn.get_remote_ip() << "> invalid message" << data;
                },
                [&](const OcppCallResult& result) {
                    std::stringstream keys;
                    for (const auto& [key, value] : result.payload) {
                        keys << magic_enum::enum_name(key) << ", ";
                    }
                    _callResultHandler.onCallResult(&conn, result);
                },
                [&](const OcppCall<OcppActionChargePoint>& call) {
                    info << conn.get_remote_ip() << "> received call: " << magic_enum::enum_name(call.action);
                    // We need to pass the message here, not the downcasted OcppCall
                    if (!_callHandler.onCall(&conn, msg)) {
                        warning << conn.get_remote_ip() << "> unhandled call: " << data;
                        return;
                    }
                    auto result = _generator.generate(call).toBuffer();
                    info << conn.get_remote_ip() << "> sending call result: " << result;
                    conn.send_text(result);
                },
            }, msg);
        })
        .onerror([&](crow::websocket::connection& conn, const std::string& data) {
            error << "> error: " << data;
            _chargePoints.removeByIp(&conn);
        });
}
