#include "OcppMeterValues.h"

namespace ocpp::calls {

using namespace ocpp::types;

std::optional<OcppMeterValues> OcppMeterValues::fromCall(const OcppCall<types::OcppActionChargePoint>& call) {
    if (!call.payload.contains(OcppCallPayloadKey::connectorId) ||
        !call.payload.contains(OcppCallPayloadKey::meterValue) ||
        !call.payload.at(OcppCallPayloadKey::connectorId).is_number() ||
        call.payload.at(OcppCallPayloadKey::connectorId).get<int>() < 0 ||
        !call.payload.at(OcppCallPayloadKey::meterValue).is_array() ||
        call.payload.at(OcppCallPayloadKey::meterValue).empty()) {
        return std::nullopt;
    }

    OcppMeterValues meterValues{call.type, call.id, call.action, call.payload};
    for (const auto& it : call.payload.at(OcppCallPayloadKey::meterValue)) {
        auto meterValue = OcppMeterValue::fromJson(it);
        if (!meterValue.has_value()) {
            return std::nullopt;
        }

        meterValues.meterValues[meterValue.value().timestamp] = meterValue.value();
    }

    return meterValues;
}

} // namespace ocpp::calls
