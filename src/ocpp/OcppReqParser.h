#pragma once

#include <ocpp/reqs/OcppReq.h>

class ChargePointRepository;

namespace crow {
namespace websocket {
class connection;
} // namespace websocket
} // namespace crow

namespace ocpp {

class OcppReqParser {
public:
    OcppReqParser();

    reqs::OcppReq parse(reqs::OcppReqBase<types::OcppActionChargePoint>&& call);

private:
    void sendGetConfiguration(crow::websocket::connection& conn);

    int _transactionId = 1;
};

} // namespace ocpp
