#include "OcppMessageHandler.h"

namespace ocpp {

OcppMessageHandler::OcppMessageHandler() {
    // Constructor implementation
}

OcppMessageHandler& OcppMessageHandler::instance() {
    static OcppMessageHandler instance; // Guaranteed to be initialized only once
    return instance;
}

const reqs::OcppReqBase<types::OcppActionCentralSystem>& OcppMessageHandler::build(types::OcppActionCentralSystem action, const types::OcppReqPayload& payload) {
    ++_transactionId;
    auto [it, inserted] = _reqs.emplace(_transactionId, reqs::OcppReqBase<types::OcppActionCentralSystem>{ std::to_string(_transactionId), action, payload });
    return it->second; // Return the reference to the inserted or found element
}

std::optional<reqs::OcppReqBase<types::OcppActionCentralSystem>> OcppMessageHandler::take(unsigned transactionId) {
    auto it = _reqs.find(transactionId);
    if (it == _reqs.end()) {
        // Return an empty std::optional if object is not found
        return std::nullopt;
    }

    // Move the object out of the map and erase the entry
    auto obj = std::move(it->second);
    _reqs.erase(it);

    // Return the moved object inside std::optional
    return obj;
}

} // namespace ocpp
