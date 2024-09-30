#pragma once

#include <string>

#include <ocpp/confs/OcppConfBase.h>
#include <ocpp/types/OcppActionCentralSystem.h>
#include <ocpp/types/OcppReqPayload.h>

namespace ocpp {

class WebSocketConnection {
public:
    void req(types::OcppActionCentralSystem action, const types::OcppReqPayload& payload);
    void conf(const confs::OcppConfBase& confBase);

private:
    //friend class OcppService;

    virtual void send(const std::string& message) = 0;
};

} // namespace ocpp
