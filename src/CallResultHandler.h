#pragma once

#include <ocpp/OcppCallResult.h>

#include "ChargePointRepository.h"

namespace crow {
namespace websocket {
class connection;
} // namespace websocket
} // namespace crow

class CallResultHandler {
public:
    CallResultHandler(ChargePointRepository& repository);

    void onCallResult(crow::websocket::connection* conn, const ocpp::OcppCallResult& callResult);

private:
    void parseConfiguration(crow::websocket::connection& conn, const nlohmann::json& value);

    ChargePointRepository& _chargePointRepository;
};
