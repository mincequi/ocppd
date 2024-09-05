#include "ResourceRoute.h"

CMRC_DECLARE(webapp);

ResourceRoute::ResourceRoute(crow::SimpleApp& app)
    : _app(app) {
    _fs = std::make_unique<cmrc::embedded_filesystem>(cmrc::webapp::get_filesystem());

    CROW_ROUTE(app, "/")
    ([this]() {
        auto file = _fs->open("index.html");
        return crow::response(200, std::string(file.begin(), file.end()));
    });

    CROW_ROUTE(app, "/<path>")
    ([this](const std::string& path) {
        if (!_fs->exists(path)) {
            CROW_LOG_ERROR << "file not found: " << path;
            return crow::response(404, "file not found: " + path);
        }

        auto file = _fs->open(path);
        return crow::response(200, std::string(file.begin(), file.end()));
    });
}
