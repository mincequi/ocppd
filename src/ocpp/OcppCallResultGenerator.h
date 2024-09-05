#pragma once

#include <ocpp/OcppCall.h>
#include <ocpp/OcppCallResult.h>

namespace ocpp {

class OcppCallResultGenerator {
public:
    OcppCallResultGenerator();

    OcppCallResult generate(const OcppCall& call);

private:
    std::string now();
};

} // namespace ocpp
