#include "OcppCallResult.h"

#include <chrono>
#include <format>
#include <iomanip>

#include <crow/json.h>
#include <magic_enum.hpp>

#include <ocpp/OcppCallResultPayloadKey.h>
#include <ocpp/OcppCallResultStatus.h>
#include <ocpp/OcppMessageType.h>

using namespace crow::json;

namespace ocpp {

std::optional<OcppCallResult> OcppCallResult::fromBuffer(const std::string& message) {
    rvalue json = load(message);
    if (!json || (json.t() != type::List) || (json.size() != 3)) {
        return std::nullopt;
    }

    const auto list = json.lo();
    if (list[0].t() != type::Number ||
        list[1].t() != type::String ||
        list[2].t() != type::Object) {
        return std::nullopt;
    }

    if (magic_enum::enum_cast<OcppMessageType>(list[0].u()) != OcppMessageType::CallResult) {
        return std::nullopt;
    }
    const auto id = list[1].s();
    OcppCallResult::Payload convertedPayload;
    for (const auto& it : list[2]) {
        const auto keyEnum = magic_enum::enum_cast<OcppCallResultPayloadKey>((std::string)it.key());
        if (!keyEnum.has_value() || it.t() != type::String) {
            return std::nullopt;
        }
        convertedPayload[keyEnum.value()] = (std::string)it;
    }

    return OcppCallResult{id, convertedPayload};
}

std::string OcppCallResult::toBuffer() const {
    wvalue::object convertedPayload;
    for (const auto& kv : payload) {
        std::visit([&](const auto& value) {
            convertedPayload[std::string(magic_enum::enum_name(kv.first))] = value;
        }, kv.second);
    }
    return wvalue({(int)OcppMessageType::CallResult, id, convertedPayload}).dump();
}

} // namespace ocpp