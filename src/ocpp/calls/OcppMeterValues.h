#pragma once

#include <optional>

#include <ocpp/OcppCall.h>
#include <ocpp/types/OcppActionChargePoint.h>
#include <ocpp/types/OcppMeterValue.h>

namespace ocpp::calls {

class OcppMeterValues : public OcppCall<types::OcppActionChargePoint> {
public:
    static std::optional<OcppMeterValues> fromCall(const OcppCall<types::OcppActionChargePoint>& call);

    std::map<unsigned, types::OcppMeterValue> meterValues;
};

} // namespace ocpp::calls
