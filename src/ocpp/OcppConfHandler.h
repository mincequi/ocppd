#pragma once

#include <typeindex>

#include <ocpp/Emitter.h>
#include <ocpp/confs/OcppConfField.h>
#include <ocpp/types/OcppConfPayloadKey.h>

#include "ChargePointRepository.h"

namespace ocpp {

class OcppConfHandler : public Emitter {
public:
    OcppConfHandler(ChargePointRepository& repository);

    void process(const ocpp::confs::OcppConfField& confField, WebSocketConnection& conn);

    template <typename ConfFieldT>
    OcppConfHandler& on(std::function<void(const ConfFieldT&, WebSocketConnection& conn)> handler) {
        auto wrappedHandler = [handler](const ocpp::confs::OcppConfField& req, WebSocketConnection& conn) {
            handler(std::get<ConfFieldT>(req), conn);
        };
        _handlers[typeid(ConfFieldT)] = wrappedHandler;
        return *this;
    }

private:
    ChargePointRepository& _chargePointRepository;

    using ConfFieldHandler = std::function<void(const ocpp::confs::OcppConfField&, WebSocketConnection&)>;
    std::map<std::type_index, ConfFieldHandler> _handlers;
};

} // namespace ocpp
