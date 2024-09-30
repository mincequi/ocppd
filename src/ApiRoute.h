#pragma once

#include <crow/app.h>
#include <nlohmann/json_fwd.hpp>

#include "ApiClientRepository.h"

class ChargePointRepository;

class ApiRoute {
public:
    ApiRoute(crow::SimpleApp& app,
            ChargePointRepository& chargePoints);

private:
    void onAction(const std::string& data);
    void onBinary(const std::string& data);
    void onProperty(const nlohmann::json& j);
    void onOcppConfiguration(const std::string& id, const nlohmann::json& j);

    crow::SimpleApp& _app;
    ChargePointRepository& _chargePoints;
    ApiClientRepository _apiClients;
};
