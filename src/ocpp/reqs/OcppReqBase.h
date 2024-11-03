#pragma once

#include <string>

#include <ocpp/types/OcppReqPayload.h>

namespace ocpp::reqs {

template<typename Action>
class OcppReqBase {
public:
    const std::string transactionId;
    const Action action;
    const types::OcppReqPayload payload;

    std::string toBuffer() const;
};

} // namespace ocpp::reqs
