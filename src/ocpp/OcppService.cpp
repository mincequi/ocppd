#include "OcppService.h"

#include <sstream>

#include <magic_enum.hpp>

#include <ocpp/OcppConfFactory.h>
#include <ocpp/OcppConfHandler.h>
#include <ocpp/OcppReqHandler.h>
#include <ocpp/utils/overload.h>

namespace ocpp {

using namespace confs;
using namespace types;

OcppService::OcppService(OcppConfHandler& confHandler,
                         OcppReqHandler& reqHandler,
                         OcppConfFactory& confFactory) :
    _confHandler(confHandler),
    _reqHandler(reqHandler),
    _confFactory(confFactory) {
    _messageParser.onInfo([this](const Emitter::Info& info) {
        if (_infoHandler) {
            _infoHandler(info);
        }
    });
    _reqHandler.onInfo([this](const Emitter::Info& info) {
        if (_infoHandler) {
            _infoHandler(info);
        }
    });
    _confFactory.onInfo([this](const Emitter::Info& info) {
        if (_infoHandler) {
            _infoHandler(info);
        }
    });
    _confHandler.onInfo([this](const Emitter::Info& info) {
        if (_infoHandler) {
            _infoHandler(info);
        }
    });
}

void OcppService::process(const std::string& data, WebSocketConnection& connection) {
    auto msg = _messageParser.parse(data);
    info("received message: " + data);
    std::visit(utils::overload {
        [&](std::nullopt_t&) {
            // Do not log anything, since the parser already logs the error
        },
        [&](OcppConfBase& result) {
            for (const auto& [key, value] : result.payload) {
                auto parseResult = _confParser.parse(key, value);
                if (std::holds_alternative<std::nullopt_t>(parseResult)) {
                    warn("unhandled conf key: " + std::string(magic_enum::enum_name(key)) + " with value: " + value.dump());
                    continue;
                }
                _confHandler.process(parseResult, connection);
            }
        },
        [&](reqs::OcppReqBase<OcppActionChargePoint>& base) {
            auto parseResult = _reqParser.parse(std::move(base));
            _reqHandler.process(parseResult, connection);
            auto conf = _confFactory.build(parseResult, connection);
            if (conf.id.empty()) {
                warn("empty id");
                return;
            }

            auto buf = conf.toBuffer();
            info("sending conf: " + buf);
            connection.send(buf);
        },
    }, msg);
}

} // namespace ocpp
