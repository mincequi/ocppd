#pragma once

#include <typeindex>

#include <ocpp/Emitter.h>
#include <ocpp/confs/OcppConfField.h>
#include <ocpp/reqs/OcppReqBase.h>
#include <ocpp/types/OcppConfPayloadKey.h>

#include "ChargePointRepository.h"

namespace ocpp {

class OcppConfHandler : public Emitter {
public:
    OcppConfHandler(ChargePointRepository& repository);

    void process(const ocpp::confs::OcppConfField& confField,
                 WebSocketConnection& conn,
                 const std::optional<reqs::OcppReqBase<types::OcppActionCentralSystem>>& req);

    template <typename ConfFieldT>
    using HandlerFunc = std::function<void(const ConfFieldT&, WebSocketConnection& conn, const std::optional<reqs::OcppReqBase<types::OcppActionCentralSystem>>&)>;

    template <typename ConfFieldT>
    OcppConfHandler& on(HandlerFunc<ConfFieldT> handler) {
        auto wrappedHandler = [handler](const ocpp::confs::OcppConfField& conf, WebSocketConnection& conn, const std::optional<reqs::OcppReqBase<types::OcppActionCentralSystem>>& req) {
            handler(std::get<ConfFieldT>(conf), conn, req);
        };
        _handlers[typeid(ConfFieldT)] = wrappedHandler;
        return *this;
    }

private:
    ChargePointRepository& _chargePointRepository;

    using ConfFieldHandler = std::function<void(const ocpp::confs::OcppConfField&, WebSocketConnection&, const std::optional<reqs::OcppReqBase<types::OcppActionCentralSystem>>&)>;
    std::map<std::type_index, ConfFieldHandler> _handlers;
};

} // namespace ocpp
