#pragma once

#include <variant>

#include <ocpp/confs/OcppConfStatus.h>
#include <ocpp/types/ConfigurationKeys.h>
#include <ocpp/types/UnknownKeys.h>

namespace ocpp::confs {

using OcppConfField = std::variant<types::ConfigurationKeys,
                                   types::UnknownKeys,
                                   OcppConfStatus,
                                   std::nullopt_t>;

} // namespace ocpp::confs
