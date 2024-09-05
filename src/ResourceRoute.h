#pragma once

#include <cmrc/cmrc.hpp>
#include <crow/app.h>

class ResourceRoute {
public:
    ResourceRoute(crow::SimpleApp& app);

private:
    crow::SimpleApp& _app;
    std::unique_ptr<cmrc::embedded_filesystem> _fs;
};
