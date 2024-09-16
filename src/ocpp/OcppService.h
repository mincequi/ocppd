#pragma once

#include <ocpp/Emitter.h>
#include <ocpp/OcppConfParser.h>
#include <ocpp/OcppReqParser.h>
#include <ocpp/OcppMessageParser.h>
#include <ocpp/WebSocketConnection.h>

namespace ocpp {

class OcppConfFactory;
class OcppConfHandler;
class OcppReqHandler;

class OcppService : public Emitter {
public:
    OcppService(OcppConfHandler& confHandler,
                OcppReqHandler& reqHandler,
                OcppConfFactory& _confFactory);

    void process(const std::string& data, WebSocketConnection& connection);

private:
    OcppMessageParser _messageParser;
    OcppConfParser _confParser;
    OcppReqParser _reqParser;
    OcppConfHandler& _confHandler;
    OcppReqHandler& _reqHandler;
    OcppConfFactory& _confFactory;
};

} // namespace ocpp
