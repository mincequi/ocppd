#include "OcppCall.h"

#include <magic_enum.hpp>

using json = nlohmann::json;

namespace ocpp {

std::string OcppCall::toBuffer() const {
    json convertedPayload;
    for (const auto& kv : payload) {
        convertedPayload[std::string(magic_enum::enum_name(kv.first))] = kv.second;
    }
    return json({(int)type, id, std::string(magic_enum::enum_name(action)), convertedPayload}).dump();
}

} // namespace ocpp
