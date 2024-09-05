#pragma once

#include <map>
#include <string>
#include <string_view>

#include <nlohmann/json_fwd.hpp>

#include <ocpp/OcppActionType.h>
#include <ocpp/OcppCall.h>
#include <ocpp/OcppCallResult.h>
#include <ocpp/action/OcppAction.h>

namespace ocpp {

class OcppMessageParser {
public:
    using ActionCallback = std::function<bool(const std::string& ip, const OcppCall::Payload& payload)>;
    using OcppMessage = std::variant<OcppCall, OcppCallResult, std::nullopt_t>;

    OcppMessageParser();

    OcppMessage parse(const std::string& message);

    const std::string& lastError() const;

    void registerAction(OcppActionType action, ActionCallback callback);

private:
    std::optional<OcppCall> parseCall(nlohmann::json& json);
    std::optional<OcppCallResult> parseCallResult(nlohmann::json& json);
    std::string _lastError;
    std::map<OcppActionType, ActionCallback> _actions;
};

} // namespace ocpp
