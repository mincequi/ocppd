#pragma once

#include <crow/app.h>

#include <ocpp/OcppMessageParser.h>
#include <ocpp/OcppCallResultGenerator.h>

#include "ActionHandler.h"

class ChargePointRepository;

class OcppRoute {
public:
    OcppRoute(crow::SimpleApp& app,
              ChargePointRepository& chargePoints);

private:
    crow::SimpleApp& _app;
    ChargePointRepository& _chargePoints;
    ocpp::OcppMessageParser _parser;
    ActionHandler _handler;
    ocpp::OcppCallResultGenerator _generator;
};
