#pragma once

#include <typeindex>

#include <ocpp/Emitter.h>
#include <ocpp/confs/OcppConfBase.h>
#include <ocpp/reqs/OcppReq.h>
#include <ocpp/types/OcppActionChargePoint.h>

namespace ocpp {
class WebSocketConnection;

class OcppConfFactory : public Emitter {
public:
    confs::OcppConfBase build(const reqs::OcppReq& req, WebSocketConnection& conn);

    template <typename ReqT>
    OcppConfFactory& on(std::function<confs::OcppConfBase(const ReqT&, WebSocketConnection&)> handler) {
        _handlers[typeid(ReqT)] = [handler](const reqs::OcppReqBase<types::OcppActionChargePoint>& req, WebSocketConnection& conn) -> confs::OcppConfBase {
            return handler(static_cast<const ReqT&>(req), conn);  // Downcast to concrete type T
        };
        return *this;
    }

private:
    std::string now();

    std::map<std::type_index, std::function<confs::OcppConfBase(const reqs::OcppReqBase<types::OcppActionChargePoint>&, WebSocketConnection&)>> _handlers;
};

} // namespace ocpp
