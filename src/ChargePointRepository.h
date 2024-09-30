#pragma once

#include <atomic>
#include <list>
#include <mutex>
#include <string>
#include <thread>

#include <ocpp/types/ConfigurationKeys.h>

#include <rpp/observables/dynamic_observable.hpp>
#include <rpp/subjects/publish_subject.hpp>

#include "ChargePoint.h"

using namespace ocpp::types;

using ChargePoints = std::map<std::string, Properties>;
using Configurations = std::map<std::string, ConfigurationKeys>;

/// \brief Repository for charge points
/// \details This class is responsible for managing charge points. It can add, remove and update
/// charge points. It also has a timer that triggers meter values for all charge points.
///
/// The repository also notifies observers when charge points are added, removed or updated.
class ChargePointRepository {
public:    
    ChargePointRepository();

    // Returns true if charge point was added, false if charge point with ip already exists
    bool add(ChargePoint&& chargePoint);

    // Returns true if charge point was removed, false if charge point with ip doesn't exist
    bool removeByIp(crow::websocket::connection* conn);

    // Get charge point by conn
    ChargePoint* byConn(crow::websocket::connection* conn) const;

    // Properties
    void setPropertiesByIp(crow::websocket::connection* conn,
                           const Properties& properties);
    void setPropertiesById(const std::string& id,
                           const Properties& properties);
    ChargePoints chargePoints();
    rpp::dynamic_observable<ChargePoints> propertiesObservable();

    // ConfigurationKeys
    void setConfigurationByIp(crow::websocket::connection* conn, const ConfigurationKeys& config);
    void setConfigurationById(const std::string& id, const ConfigurationKeys& config);
    Configurations configurations();
    rpp::dynamic_observable<Configurations> configurationObservable();

    void triggerMeterValues();

private:
    void startTimer();
    void stopTimer();

    rpp::subjects::publish_subject<ChargePoints> _propertiesSubject;
    rpp::subjects::publish_subject<Configurations> _configurationsSubject;

    std::mutex _mutex;
    std::list<ChargePoint> _chargePoints;
    std::atomic<bool> _isTimerRunning = false;
    std::thread _timerThread;
};
