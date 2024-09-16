#include "MeterValues.h"

namespace ocpp::reqs {

using namespace ocpp::types;

std::optional<MeterValues> MeterValues::fromBase(const OcppReqBase<types::OcppActionChargePoint>& call) {
    if (!call.payload.contains(OcppReqPayloadKey::connectorId) ||
        !call.payload.contains(OcppReqPayloadKey::meterValue) ||
        !call.payload.at(OcppReqPayloadKey::connectorId).is_number() ||
        call.payload.at(OcppReqPayloadKey::connectorId).get<int>() < 0 ||
        !call.payload.at(OcppReqPayloadKey::meterValue).is_array() ||
        call.payload.at(OcppReqPayloadKey::meterValue).empty()) {
        return std::nullopt;
    }

    MeterValues meterValues{call.type, call.id, call.action, call.payload};
    for (const auto& it : call.payload.at(OcppReqPayloadKey::meterValue)) {
        auto meterValue = OcppMeterValue::fromJson(it);
        if (!meterValue.has_value()) {
            continue;
        }

        meterValues.meterValues[meterValue.value().timestamp] = meterValue.value();
    }

    return meterValues;
}

} // namespace ocpp::reqs
