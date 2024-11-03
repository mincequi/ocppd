#pragma once

#include <ocpp/reqs/OcppReqBase.h>
#include <ocpp/types/OcppActionCentralSystem.h>
#include <ocpp/types/OcppConfigurationKey.h>
#include <ocpp/types/OcppMeasurand.h>

namespace ocpp::reqs {

class ChangeConfiguration : public OcppReqBase<types::OcppActionCentralSystem> {
public:
    using Value = std::variant<std::vector<types::OcppMeasurand>>;

    ChangeConfiguration(types::OcppConfigurationKey key, Value value);
};

} // namespace ocpp::reqs
