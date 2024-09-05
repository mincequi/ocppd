#include "OcppMessageParser.h"

#include <magic_enum.hpp>
#include <nlohmann/json.hpp>

#include "OcppActionType.h"
#include "OcppMessageType.h"

using json = nlohmann::json;

namespace ocpp {

OcppMessageParser::OcppMessageParser() {
}

OcppMessageParser::OcppMessage OcppMessageParser::parse(const std::string& message) {
    _lastError.clear();
    json data = json::parse(message);
    if (!data.is_array()) {
        return std::nullopt;
    }

    const auto call = parseCall(data);
    if (call.has_value()) {
        return call.value();
    }

    const auto callResult = parseCallResult(data);
    if (callResult.has_value()) {
        return callResult.value();
    }

    _lastError = "invalid message format";
    return std::nullopt;
}

const std::string& OcppMessageParser::lastError() const {
    return _lastError;
}

void OcppMessageParser::registerAction(OcppActionType action, ActionCallback callback) {
    _actions[action] = callback;
}

std::optional<OcppCall> OcppMessageParser::parseCall(json& array) {
    if (array.size() != 4) {
        return std::nullopt;
    }

    if (!array[0].is_number() ||
        !array[1].is_string() ||
        !array[2].is_string() ||
        !array[3].is_object()) {
        return std::nullopt;
    }

    const auto type = magic_enum::enum_cast<OcppMessageType>(array[0].get<int>());
    if (!type.has_value()) {
        return std::nullopt;
    }
    const auto id = array[1].get<std::string>();
    const auto action = magic_enum::enum_cast<OcppActionType>((std::string)array[2]);
    if (!action.has_value()) {
        return std::nullopt;
    }

    OcppCall::Payload convertedPayload;
    for (const auto& it : array[3].items()) {
        const auto keyEnum = magic_enum::enum_cast<OcppCallPayloadKey>(it.key());
        if (!keyEnum.has_value()) {
            return std::nullopt;
        }
        convertedPayload[keyEnum.value()] = it.value();
    }

    return OcppCall{type.value(), id, action.value(), convertedPayload};
}

std::optional<OcppCallResult> OcppMessageParser::parseCallResult(json& list) {
    if (list.size() != 3) {
        return std::nullopt;
    }

    if (!list[0].is_number_integer() ||
        !list[1].is_string() ||
        !list[2].is_object()) {
        return std::nullopt;
    }

    if (magic_enum::enum_cast<OcppMessageType>(list[0].get<int>()) != OcppMessageType::CallResult) {
        return std::nullopt;
    }
    const auto id = list[1].get<std::string>();
    OcppCallResult::Payload convertedPayload;
    for (const auto& it : list[2].items()) {
        const auto keyEnum = magic_enum::enum_cast<OcppCallResultPayloadKey>(it.key());
        if (!keyEnum.has_value()) {
            return std::nullopt;
        }
        convertedPayload[keyEnum.value()] = (std::string)it.value();
    }

    return OcppCallResult{id, convertedPayload};
}

} // namespace ocpp
