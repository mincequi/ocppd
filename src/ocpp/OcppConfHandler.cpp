#include "OcppConfHandler.h"

#include <magic_enum.hpp>

using namespace ocpp::types;

namespace ocpp {

using namespace confs;

OcppConfHandler::OcppConfHandler(ChargePointRepository& repository)
    : _chargePointRepository(repository) {

    on<OcppConfStatus>([&](const OcppConfStatus& status, WebSocketConnection& conn, const std::optional<reqs::OcppReqBase<types::OcppActionCentralSystem>>& req) {
        if (!req) {
            warn("status without a request");
            return;
        }

        if (status == OcppConfStatus::Accepted) {
            info("req: " + std::string(magic_enum::enum_name(req->action)) + " accepted");
        } else {
            warn("req: " + std::string(magic_enum::enum_name(req->action)) + " not accepted with status: " + std::string(magic_enum::enum_name(status)));
        }
    });
}

void OcppConfHandler::process(const ocpp::confs::OcppConfField& confField,
                              WebSocketConnection& conn,
                              const std::optional<reqs::OcppReqBase<types::OcppActionCentralSystem>>& req) {
    return std::visit([&](auto&& conf) {
        using T = std::decay_t<decltype(conf)>;  // Deduce the actual type of the request
        auto it = _handlers.find(typeid(T));    // Find the handler for the request type
        if (it != _handlers.end()) {
            it->second(confField, conn, req);  // Call the appropriate handler
        } else {
            warn("unhandled conf field with type id: " + std::string(typeid(T).name()));
        }
    }, confField);
}

} // namespace ocpp
