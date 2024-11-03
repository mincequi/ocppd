#include "OcppReqBase.h"

#include <magic_enum.hpp>

#include <ocpp/types/OcppActionCentralSystem.h>
#include <ocpp/types/OcppActionChargePoint.h>
#include <ocpp/types/OcppMessageType.h>

using json = nlohmann::json;

namespace ocpp::reqs {

using namespace types;

template<typename ActionType>
std::string OcppReqBase<ActionType>::toBuffer() const {
    json convertedPayload;
    for (const auto& kv : payload) {
        convertedPayload[std::string(magic_enum::enum_name(kv.first))] = kv.second;
    }
    return json({(int)OcppMessageType::Call, transactionId, std::string(magic_enum::enum_name(action)), convertedPayload}).dump();
}

template class OcppReqBase<OcppActionCentralSystem>;
template class OcppReqBase<OcppActionChargePoint>;

} // namespace ocpp::reqs
