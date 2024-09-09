#pragma once

#include <crow/app.h>

#include "ApiClientRepository.h"

class ChargePointRepository;

class ApiRoute {
public:
    ApiRoute(crow::SimpleApp& app,
            ChargePointRepository& chargePoints);

private:
    void onAction(const std::string& data);
    void onProperty(const std::string& data);

    crow::SimpleApp& _app;
    ChargePointRepository& _chargePoints;
    ApiClientRepository _apiClients;
};
