#include "OcppReqBase.h"

#include <magic_enum.hpp>

#include <ocpp/types/OcppActionCentralSystem.h>
#include <ocpp/types/OcppActionChargePoint.h>

using json = nlohmann::json;

namespace ocpp::reqs {

template<typename ActionType>
std::string OcppReqBase<ActionType>::toBuffer() const {
    json convertedPayload;
    for (const auto& kv : payload) {
        convertedPayload[std::string(magic_enum::enum_name(kv.first))] = kv.second;
    }
    return json({(int)type, id, std::string(magic_enum::enum_name(action)), convertedPayload}).dump();
}

template class OcppReqBase<types::OcppActionCentralSystem>;
template class OcppReqBase<types::OcppActionChargePoint>;

} // namespace ocpp::reqs
