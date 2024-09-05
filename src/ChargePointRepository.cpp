#include "ChargePointRepository.h"

#include <crow/websocket.h>
#include <rpp/observers/observer.hpp>

#include <ocpp/OcppCall.h>

using namespace ocpp;

ChargePointRepository::ChargePointRepository() {}

bool ChargePointRepository::add(ChargePoint&& chargePoint) {
    std::lock_guard<std::mutex> _(_mutex);
    // If charge point with ip already exists, don't add it again
    if (std::find_if(_chargePoints.begin(), _chargePoints.end(), [&chargePoint](const ChargePoint& cp) {
            return cp == chargePoint;
        }) != _chargePoints.end()) {
        return false;
    }

    _chargePoints.push_back(chargePoint);
    return true;
}

bool ChargePointRepository::removeByIp(crow::websocket::connection& conn) {
    std::lock_guard<std::mutex> _(_mutex);
    // Check if charge point with ip exists
    if (std::find_if(_chargePoints.begin(), _chargePoints.end(), [&](const ChargePoint& cp) {
            return cp.remoteIp() == conn.get_remote_ip();
        }) == _chargePoints.end()) {
        return false;
    }

    _chargePoints.remove_if([&](const ChargePoint& cp) {
        return cp.remoteIp() == conn.get_remote_ip();
    });

    stopTimer();
    return true;
}

void ChargePointRepository::setPropertiesByIp(crow::websocket::connection& conn,
                                              const Properties& properties) {
    {
        std::lock_guard<std::mutex> _(_mutex);
        auto it = std::find_if(_chargePoints.begin(), _chargePoints.end(), [&](const ChargePoint& cp) {
            return cp.remoteIp() == conn.get_remote_ip();
        });

        if (it != _chargePoints.end()) {
            it->setProperties(properties);
            _chargePointsSubject.get_observer().on_next({{ it->_id, properties }});
        }
    }

    // If status was updated, start or stop the timer
    if (properties.contains(PropertyKey::status)) {
        if (std::get<OcppCallStatus>(properties.at(PropertyKey::status)) == OcppCallStatus::Charging) {
            startTimer();
        } else {
            stopTimer();
        }
    }
}

void ChargePointRepository::setPropertiesById(const std::string& id,
                                              const Properties& properties) {
    std::lock_guard<std::mutex> _(_mutex);
    auto it = std::find_if(_chargePoints.begin(), _chargePoints.end(), [&](const ChargePoint& cp) {
        return cp._id == id;
    });

    if (it != _chargePoints.end()) {
        it->setProperties(properties);
        _chargePointsSubject.get_observer().on_next({{ it->_id, properties }});
    }
}

ChargePoints ChargePointRepository::chargePoints() {
    std::lock_guard<std::mutex> _(_mutex);
    ChargePoints cps;
    for (const auto& cp : _chargePoints) {
        cps[cp._id] = cp.properties();
    }
    return cps;
}

rpp::dynamic_observable<ChargePoints> ChargePointRepository::chargePointsObservable() {
    return _chargePointsSubject.get_observable();
}

void ChargePointRepository::startTimer() {
    if (!_isTimerRunning) {
        _isTimerRunning = true;
        _timerThread = std::thread([&]() {
            while (_isTimerRunning) {
                triggerMeterValues();
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        });
    }
}

void ChargePointRepository::stopTimer() {
    bool isAnyChargePointCharging = false;

    {
        std::lock_guard<std::mutex> _(_mutex);
        for (const auto& cp : _chargePoints) {
            if (cp.properties().contains(PropertyKey::status) &&
                std::get<OcppCallStatus>(cp.properties().at(PropertyKey::status)) == OcppCallStatus::Charging) {
                isAnyChargePointCharging = true;
                break;
            }
        }
    }

    if (_isTimerRunning && !isAnyChargePointCharging) {
        _isTimerRunning = false;
        _timerThread.join();
    }
    triggerMeterValues();
}

void ChargePointRepository::triggerMeterValues() {
    std::lock_guard<std::mutex> _(_mutex);
    for (auto& cp : _chargePoints) {
        OcppCall call { OcppMessageType::Call, std::to_string(_transactionId++), OcppActionType::TriggerMessage,
                      { { OcppCallPayloadKey::requestedMessage, "MeterValues" },
                          { OcppCallPayloadKey::connectorId, 1 }
                      } };
        cp._connection.send_text(call.toBuffer());
    }
}
