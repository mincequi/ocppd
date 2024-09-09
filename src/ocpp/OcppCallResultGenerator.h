#pragma once

#include <ocpp/OcppCall.h>
#include <ocpp/OcppCallResult.h>
#include <ocpp/types/OcppActionChargePoint.h>

namespace ocpp {

class OcppCallResultGenerator {
public:
    OcppCallResultGenerator();

    OcppCallResult generate(const OcppCall<types::OcppActionChargePoint>& call);

private:
    std::string now();
};

} // namespace ocpp
