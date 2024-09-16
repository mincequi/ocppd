#pragma once

#include <string>

#include <ocpp/types/OcppMessageType.h>
#include <ocpp/types/OcppReqPayload.h>

namespace ocpp::reqs {

//template<auto Action>
template<typename Action>
class OcppReqBase {
public:
    const types::OcppMessageType type;
    const std::string id;
    //const decltype(Action) action = Action;
    const Action action;
    const types::OcppReqPayload payload;

    std::string toBuffer() const;
};

} // namespace ocpp::reqs
