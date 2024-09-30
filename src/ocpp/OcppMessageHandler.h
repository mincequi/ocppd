#pragma once

#include <ocpp/reqs/OcppReqBase.h>
#include <ocpp/types/OcppActionCentralSystem.h>

namespace ocpp {

#define messageHandler OcppMessageHandler::instance()

class OcppMessageHandler {
public:
    static OcppMessageHandler& instance();

    const reqs::OcppReqBase<types::OcppActionCentralSystem>& build(types::OcppActionCentralSystem action, const types::OcppReqPayload& payload);
    std::optional<reqs::OcppReqBase<types::OcppActionCentralSystem>> take(unsigned transactionId);

private:
    OcppMessageHandler();

    std::map<unsigned, reqs::OcppReqBase<types::OcppActionCentralSystem>> _reqs;

    unsigned _transactionId = 0;
};

} // namespace ocpp
