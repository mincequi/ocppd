#pragma once

#include <map>
#include <string>
#include <string_view>

#include <nlohmann/json_fwd.hpp>

#include <ocpp/OcppCall.h>
#include <ocpp/OcppCallResult.h>
#include <ocpp/calls/OcppMeterValues.h>
#include <ocpp/types/OcppActionChargePoint.h>
#include <ocpp/types/OcppMessage.h>
#include <ocpp/types/OcppCallPayload.h>

namespace ocpp {

class OcppMessageParser {
public:
    using ActionCallback = std::function<bool(const std::string& ip, const types::OcppCallPayload& payload)>;

    OcppMessageParser();

    types::OcppMessage parse(const std::string& message);

    const std::string& lastError() const;

    void registerAction(types::OcppActionChargePoint action, ActionCallback callback);

private:
    types::OcppMessage parseCall(nlohmann::json& json);
    std::optional<OcppCallResult> parseCallResult(nlohmann::json& json);
    std::string _lastError;
    std::map<types::OcppActionChargePoint, ActionCallback> _actions;
};

} // namespace ocpp
