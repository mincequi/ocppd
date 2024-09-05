#pragma once

#include <mutex>

#include <ocpp/OcppActionHandler.h>
#include <ocpp/OcppCall.h>

class ChargePointRepository;

namespace crow {
namespace websocket {
class connection;
} // namespace websocket
} // namespace crow

class ActionHandler : public ocpp::OcppActionHandler {
public:
    ActionHandler(ChargePointRepository& repository);

    bool onCall(const ocpp::OcppCall& call, void* userData = nullptr) override;

private:
    bool onBootNotification(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn);
    bool onHeartbeat(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn);
    bool onStatusNotification(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn);
    bool onMeterValues(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn);
    bool onStartTransaction(const ocpp::OcppCall::Payload& payload, crow::websocket::connection& conn);

    ChargePointRepository& _repository;

    int _transactionId = 1;
};
