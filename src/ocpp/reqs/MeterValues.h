#pragma once

#include <optional>

#include <ocpp/reqs/OcppReqBase.h>
#include <ocpp/types/OcppActionChargePoint.h>
#include <ocpp/types/OcppMeterValue.h>

namespace ocpp::reqs {

class MeterValues : public OcppReqBase<types::OcppActionChargePoint> {
public:
    static std::optional<MeterValues> fromBase(const OcppReqBase<types::OcppActionChargePoint>& call);

    std::map<unsigned, types::OcppMeterValue> meterValues;
};

} // namespace ocpp::reqs
