#include <crow.h>

#include <ApiRoute.h>
#include <ChargePointRepository.h>
#include <OcppRoute.h>
#include <ResourceRoute.h>

static uint16_t port = 8030;

using namespace ocpp;

int main() {
    crow::SimpleApp app;

#ifndef DEBUG
    app.loglevel(crow::LogLevel::Warning);
#endif

    ChargePointRepository chargePoints;
    OcppRoute ocppRoute(app, chargePoints);
    ApiRoute apiRoute(app, chargePoints);
    ResourceRoute resourceRoute(app);

    app.port(port)
       .multithreaded()
       .run();
}
