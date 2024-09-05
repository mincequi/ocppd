#pragma once

#include <atomic>
#include <list>
#include <mutex>
#include <string>
#include <thread>

#include <rpp/observables/dynamic_observable.hpp>
#include <rpp/subjects/publish_subject.hpp>

#include "ChargePoint.h"

class ChargePointRepository {
public:
    ChargePointRepository();

    // Returns true if charge point was added, false if charge point with ip already exists
    bool add(ChargePoint&& chargePoint);

    // Returns true if charge point was removed, false if charge point with ip doesn't exist
    bool removeByIp(crow::websocket::connection& conn);

    void setPropertiesByIp(crow::websocket::connection& conn,
                           const Properties& properties);

    void setPropertiesById(const std::string& id,
                           const Properties& properties);

    ChargePoints chargePoints();
    rpp::dynamic_observable<ChargePoints> chargePointsObservable();

private:
    void startTimer();
    void stopTimer();
    void triggerMeterValues();

    rpp::subjects::publish_subject<ChargePoints> _chargePointsSubject;

    std::mutex _mutex;
    std::list<ChargePoint> _chargePoints;
    std::atomic<bool> _isTimerRunning = false;
    std::thread _timerThread;

    int _transactionId = 1;
};
