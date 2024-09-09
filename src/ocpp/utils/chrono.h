#pragma once

#include <string>

namespace ocpp::utils {

// Parse iso8601 string potentially including milliseconds to seconds since epoch
unsigned parseIso8601ToEpoch(const std::string& isoTimestamp);

} // namespace ocpp::utils
