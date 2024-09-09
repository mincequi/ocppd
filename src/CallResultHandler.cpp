#include "CallResultHandler.h"

#include <magic_enum.hpp>

#include <ocpp/types/OcppCallResultPayloadKey.h>
#include <ocpp/types/OcppConfiguration.h>

#include "utils/log.h"

using namespace ocpp::types;

CallResultHandler::CallResultHandler(ChargePointRepository& repository)
    : _chargePointRepository(repository) {
}

void CallResultHandler::onCallResult(crow::websocket::connection* conn, const ocpp::OcppCallResult& callResult) {
    for (const auto& [key, value] : callResult.payload) {
        switch (key) {
        case OcppCallResultPayloadKey::configurationKey:
            parseConfiguration(*conn, value);
            break;
        default:
            break;
        }
    }
}

void CallResultHandler::parseConfiguration(crow::websocket::connection& conn, const nlohmann::json& value) {
    if (!value.is_array()) {
        return;
    }

    OcppConfiguration configuration;
    for (const auto& item : value) {
        if (!item.is_object() ||
            !item.contains("key") ||
            !item.contains("value") ||
            !item.contains("readonly") ||
            !item["key"].is_string() ||
            !item["value"].is_string() ||
            !item["readonly"].is_boolean() ||
            item["readonly"].get<bool>()) {
            continue;
        }

        const auto key = magic_enum::enum_cast<OcppConfigurationKey>(item["key"].get<std::string>());
        if (!key.has_value()) {
            continue;
        }

        configuration[key.value()] = item["value"].get<std::string>();
    }

    _chargePointRepository.setConfigurationByIp(&conn, configuration);
}
