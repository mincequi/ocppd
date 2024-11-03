#include "ChargePointRepository.h"

#include <crow/websocket.h>
#include <magic_enum.hpp>
#include <rpp/observers/observer.hpp>

#include <ocpp/reqs/OcppReqBase.h>
#include <ocpp/types/OcppActionCentralSystem.h>

using namespace ocpp;
using namespace ocpp::types;

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

bool ChargePointRepository::removeByIp(crow::websocket::connection* conn) {
    std::lock_guard<std::mutex> _(_mutex);
    // Check if charge point with ip exists
    if (std::find_if(_chargePoints.begin(), _chargePoints.end(), [&](const ChargePoint& cp) {
            return cp._connection == conn;
        }) == _chargePoints.end()) {
        return false;
    }

    _chargePoints.remove_if([&](const ChargePoint& cp) {
        return cp._connection == conn;
    });

    stopTimer();
    return true;
}

ChargePoint* ChargePointRepository::byConn(crow::websocket::connection* conn) const {
    auto it = std::find_if(_chargePoints.begin(), _chargePoints.end(), [&](const ChargePoint& cp) {
        return cp._connection == conn;
    });

    if (it != _chargePoints.end()) {
        return const_cast<ChargePoint*>(&(*it));
    }

    return nullptr;
}

void ChargePointRepository::setPropertiesByIp(crow::websocket::connection* conn,
                                              const Properties& properties) {
    {
        std::lock_guard<std::mutex> _(_mutex);
        auto it = std::find_if(_chargePoints.begin(), _chargePoints.end(), [&](const ChargePoint& cp) {
            return cp._connection == conn;
        });

        if (it != _chargePoints.end()) {
            it->setProperties(properties);
            _propertiesSubject.get_observer().on_next({{ it->_id, properties }});
        }
    }

    // If status was updated, start or stop the timer
    if (properties.contains(PropertyKey::status)) {
        if (std::get<OcppChargePointStatus>(properties.at(PropertyKey::status)) == OcppChargePointStatus::Charging) {
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
        _propertiesSubject.get_observer().on_next({{ it->_id, properties }});
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

rpp::dynamic_observable<std::map<std::string, Properties>> ChargePointRepository::propertiesObservable() {
    return _propertiesSubject.get_observable();
}

void ChargePointRepository::setConfigurationByIp(crow::websocket::connection* conn, const ConfigurationKeys& config) {
    std::lock_guard<std::mutex> _(_mutex);
    auto it = std::find_if(_chargePoints.begin(), _chargePoints.end(), [&](const ChargePoint& cp) {
        return cp._connection == conn;
    });

    if (it != _chargePoints.end()) {
        it->setConfiguration(config);
    }
}

void ChargePointRepository::req(const std::string& id, types::OcppActionCentralSystem action, const types::OcppReqPayload& payload) {
    std::lock_guard<std::mutex> _(_mutex);
    auto it = std::find_if(_chargePoints.begin(), _chargePoints.end(), [&](const ChargePoint& cp) {
        return cp._id == id;
    });

    if (it != _chargePoints.end()) {
        it->req(action, payload);
    }
}

std::map<std::string, ConfigurationKeys> ChargePointRepository::configurations() {
    std::lock_guard<std::mutex> _(_mutex);
    std::map<std::string, ConfigurationKeys> configs;
    for (const auto& cp : _chargePoints) {
        configs[cp._id] = cp.configuration();
    }
    return configs;
}

rpp::dynamic_observable<std::map<std::string, ConfigurationKeys>> ChargePointRepository::configurationObservable() {
    return _configurationsSubject.get_observable();
}

void ChargePointRepository::triggerMeterValues() {
    std::lock_guard<std::mutex> _(_mutex);
    for (auto& cp : _chargePoints) {
        //reqs::OcppReqBase<OcppActionCentralSystem> call {
        //    "TriggerMessage " + std::to_string(++_transactionId),
        //    OcppActionCentralSystem::TriggerMessage,
        //    { { OcppReqPayloadKey::requestedMessage, "MeterValues" },
        //        { OcppReqPayloadKey::connectorId, 1 }
        //    }
        //};
        //cp._connection->send_text(call.toBuffer());
        cp.req(OcppActionCentralSystem::TriggerMessage, {
            { OcppReqPayloadKey::requestedMessage, "MeterValues" },
            { OcppReqPayloadKey::connectorId, 1 } });
    }
}

void ChargePointRepository::startTimer() {
    if (!_isTimerRunning) {
        _isTimerRunning = true;
        _timerThread = std::thread([&]() {
            while (_isTimerRunning) {
                //triggerMeterValues();
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
                std::get<OcppChargePointStatus>(cp.properties().at(PropertyKey::status)) == OcppChargePointStatus::Charging) {
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
