#pragma once

#include <ocpp/OcppCallHandler.h>
#include <ocpp/types/OcppMessage.h>

class ChargePointRepository;

namespace crow {
namespace websocket {
class connection;
} // namespace websocket
} // namespace crow

using namespace ocpp;
using namespace ocpp::types;

class CallHandler : public ocpp::OcppCallHandler {
public:
    CallHandler(ChargePointRepository& repository);

    bool onCall(void* userData, const OcppMessage& call) override;

private:
    void sendGetConfiguration(crow::websocket::connection& conn);

    bool onBootNotification(const OcppCallPayload& payload, crow::websocket::connection& conn);
    bool onHeartbeat(const OcppCallPayload& payload, crow::websocket::connection& conn);
    bool onStatusNotification(const OcppCallPayload& payload, crow::websocket::connection& conn);
    bool onMeterValues(const calls::OcppMeterValues& call, crow::websocket::connection& conn);
    bool onStartTransaction(const OcppCallPayload& payload, crow::websocket::connection& conn);
    bool onStopTransaction(const OcppCallPayload& payload, crow::websocket::connection& conn);

    ChargePointRepository& _repository;

    int _transactionId = 1;
};
