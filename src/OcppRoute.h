#pragma once

#include <crow/app.h>

#include <ocpp/OcppConfFactory.h>
#include <ocpp/OcppConfHandler.h>
#include <ocpp/OcppReqHandler.h>
#include <ocpp/OcppService.h>

class ChargePointRepository;

class OcppRoute {
public:
    OcppRoute(crow::SimpleApp& app,
              ChargePointRepository& chargePoints);

private:    
    crow::SimpleApp& _app;
    ChargePointRepository& _chargePoints;
    ocpp::OcppConfFactory _confFactory;
    ocpp::OcppConfHandler _confHandler;
    ocpp::OcppReqHandler _reqHandler;
    ocpp::OcppService _service;

    std::mutex _mutex;
};
