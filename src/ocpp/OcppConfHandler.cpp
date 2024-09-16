#include "OcppConfHandler.h"

using namespace ocpp::types;

namespace ocpp {

OcppConfHandler::OcppConfHandler(ChargePointRepository& repository)
    : _chargePointRepository(repository) {
}

void OcppConfHandler::process(const ocpp::confs::OcppConfField& confField, WebSocketConnection& conn) {
    return std::visit([&](auto&& req) {
        using T = std::decay_t<decltype(req)>;  // Deduce the actual type of the request
        auto it = _handlers.find(typeid(T));    // Find the handler for the request type
        if (it != _handlers.end()) {
            it->second(confField, conn);  // Call the appropriate handler
        } else {
            warn("unhandled conf field with type id: " + std::string(typeid(T).name()));
        }
    }, confField);
}

} // namespace ocpp
