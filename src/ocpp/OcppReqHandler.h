#pragma once

#include <typeindex>
#include <variant>

#include <ocpp/Emitter.h>
#include <ocpp/reqs/OcppReq.h>
#include <ocpp/types/OcppMessage.h>

class ChargePointRepository;

namespace crow {
namespace websocket {
class connection;
} // namespace websocket
} // namespace crow

namespace ocpp {
class WebSocketConnection;

class OcppReqHandler : public Emitter {
public:
    OcppReqHandler(ChargePointRepository& repository);

    void process(reqs::OcppReq& req, WebSocketConnection& connection);

    template <typename ReqT>
    OcppReqHandler& on(std::function<void(const ReqT&, WebSocketConnection&)> handler) {
        _handlers[typeid(ReqT)] = [handler](const reqs::OcppReqBase<types::OcppActionChargePoint>& req, WebSocketConnection& conn) {
            handler(static_cast<const ReqT&>(req), conn);  // Downcast to concrete type T
        };
        return *this;
    }

private:
    void sendGetConfiguration(crow::websocket::connection& conn);

    ChargePointRepository& _repository;

    std::map<std::type_index, std::function<void(const reqs::OcppReqBase<types::OcppActionChargePoint>&, WebSocketConnection&)>> _handlers;

    int _transactionId = 1;
};

} // namespace ocpp
