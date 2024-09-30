#include "WebSocketConnection.h"

#include <ocpp/OcppMessageHandler.h>
#include <ocpp/reqs/OcppReqBase.h>

namespace ocpp {

void WebSocketConnection::req(types::OcppActionCentralSystem action, const types::OcppReqPayload& payload) {
    auto req = messageHandler.build(action, payload);
    send(req.toBuffer());
}

void WebSocketConnection::conf(const confs::OcppConfBase& confBase) {
    send(confBase.toBuffer());
}

} // namespace ocpp
