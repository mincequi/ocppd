#pragma once

#include <string>
#include <sstream>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_TO_STRING(message) \
    ([](const auto& msg) -> std::string { \
            std::ostringstream oss; \
            oss << __FILENAME__ << ":" << __LINE__ << "> " << msg; \
            return oss.str(); \
    }(message))
#define info(message) if (_infoHandler) { _infoHandler({Emitter::Info::Severity::Info, LOG_TO_STRING(message)}); }
#define warn(message) if (_infoHandler) { _infoHandler({Emitter::Info::Severity::Warning, LOG_TO_STRING(message)}); }
#define err(message) if (_infoHandler) { _infoHandler({Emitter::Info::Severity::Error, LOG_TO_STRING(message)}); }

class Emitter {
public:
    struct Info {
        enum class Severity {
            Info,
            Warning,
            Error,
        } severity;
        std::string message;
    };

    Emitter();

    Emitter& onInfo(std::function<void(const Info&)> handler);

protected:
    using InfoHandler = std::function<void(const Info&)>;
    InfoHandler _infoHandler;
};
