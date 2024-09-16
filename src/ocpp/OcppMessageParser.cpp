#include "OcppMessageParser.h"

#include <magic_enum.hpp>
#include <nlohmann/json.hpp>

#include "reqs/MeterValues.h"
#include "types/OcppActionChargePoint.h"
#include "types/OcppMessageType.h"

using json = nlohmann::json;
using namespace ocpp::types;

namespace ocpp {

using namespace reqs;
using namespace types;

OcppMessageParser::OcppMessageParser() {
}

OcppMessage OcppMessageParser::parse(const std::string& message) {
    json data = json::parse(message);
    if (!data.is_array()) {
        warn("invalid json: " + message);
        return std::nullopt;
    }

    const auto call = parseCall(data);
    if (!std::holds_alternative<std::nullopt_t>(call)) {
        return call;
    }

    const auto callResult = parseCallResult(data);
    if (callResult.has_value()) {
        return callResult.value();
    }

    warn("invalid message: " + message);
    return std::nullopt;
}

OcppMessage OcppMessageParser::parseCall(json& array) {
    if (array.size() != 4) {
        // do not warn here, since this might be a result
        //warn("invalid call array size: " + array.dump());
        return std::nullopt;
    }

    if (!array[0].is_number() ||
        !array[1].is_string() ||
        !array[2].is_string() ||
        !array[3].is_object()) {
        warn("invalid call array types: " + array.dump());
        return std::nullopt;
    }

    const auto type = magic_enum::enum_cast<OcppMessageType>(array[0].get<int>());
    if (!type.has_value()) {
        warn("invalid call type: " + array.dump());
        return std::nullopt;
    }
    const auto id = array[1].get<std::string>();
    const auto action = magic_enum::enum_cast<OcppActionChargePoint>((std::string)array[2]);
    if (!action.has_value()) {
        warn("invalid call action: " + array.dump());
        return std::nullopt;
    }

    OcppReqPayload convertedPayload;
    for (const auto& it : array[3].items()) {
        const auto keyEnum = magic_enum::enum_cast<OcppReqPayloadKey>(it.key());
        if (!keyEnum.has_value()) {
            warn("invalid call payload key: " + it.key());
            continue;
        }
        convertedPayload[keyEnum.value()] = it.value();
    }

    return OcppReqBase<OcppActionChargePoint>{type.value(), id, action.value(), convertedPayload};
}

std::optional<confs::OcppConfBase> OcppMessageParser::parseCallResult(json& list) {
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
    confs::OcppConfBase::Payload convertedPayload;
    for (const auto& it : list[2].items()) {
        const auto keyEnum = magic_enum::enum_cast<OcppConfPayloadKey>(it.key());
        if (!keyEnum.has_value()) {
            return std::nullopt;
        }
        convertedPayload[keyEnum.value()] = it.value();
    }

    return confs::OcppConfBase{id, convertedPayload};
}

} // namespace ocpp
