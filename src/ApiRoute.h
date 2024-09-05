#pragma once

#include <crow/app.h>

#include "ApiClientRepository.h"

class ChargePointRepository;

class ApiRoute {
public:
    ApiRoute(crow::SimpleApp& app,
            ChargePointRepository& chargePoints);

private:
    void sendChargePoints(crow::websocket::connection& conn);

    crow::SimpleApp& _app;
    ChargePointRepository& _chargePoints;
    ApiClientRepository _apiClients;
};
