#include "OcppConfBase.h"

#include <magic_enum.hpp>

#include <ocpp/types/OcppMessageType.h>

using namespace ocpp::types;
using json = nlohmann::json;

namespace ocpp::confs {

std::string OcppConfBase::toBuffer() const {
    json convertedPayload;
    for (const auto& kv : payload) {
        convertedPayload[std::string(magic_enum::enum_name(kv.first))] = kv.second;
    }
    return json({(int)OcppMessageType::CallResult, id, convertedPayload}).dump();
}

} // namespace ocpp::confs
