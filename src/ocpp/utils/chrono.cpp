#include "chrono.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>

namespace ocpp::utils {

unsigned parseIso8601ToEpoch(const std::string& isoTimestamp) {
    std::tm timeStruct = {};
    std::istringstream ss(isoTimestamp);

    // Extract the milliseconds part if present
    char delim;
    double fractional_seconds = 0;

    // Parse date and time (YYYY-MM-DDTHH:MM:SS)
    ss >> std::get_time(&timeStruct, "%Y-%m-%dT%H:%M:%S");

    // Check if we have milliseconds (fractional seconds)
    if (ss.peek() == '.') {
        ss >> delim; // Consume the '.'
        ss >> fractional_seconds; // Get the milliseconds, but we'll ignore it
    }

    // Check for the 'Z' at the end (indicating UTC)
    ss >> delim; // Consume the 'Z'

    if (ss.fail()) {
        throw std::runtime_error("Failed to parse time string");
    }

    // Convert the time struct to time_t (seconds since epoch, UTC)
    time_t timeSinceEpoch = timegm(&timeStruct);

    return static_cast<long long>(timeSinceEpoch);
}

} // namespace ocpp::utils
