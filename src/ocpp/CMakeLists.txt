add_library(ocpp STATIC
  confs/OcppConfBase.h
  confs/OcppConfBase.cpp
  OcppConfHandler.cpp
  OcppReqHandler.cpp
  OcppConfFactory.h
  OcppConfFactory.cpp
  OcppMessageParser.cpp
  WebSocketConnection.h
  action/OcppAction.cpp
  action/OcppAction.h
  action/OcppActionBootNotification.h
  action/OcppActionBootNotification.cpp
  reqs/MeterValues.h
  reqs/MeterValues.cpp
  types/OcppActionCentralSystem.h
  types/OcppActionChargePoint.h
  types/OcppReqPayload.h
  types/OcppReqPayloadKey.h
  types/OcppConfPayloadKey.h
  confs/OcppConfStatus.h
  types/OcppReqStatus.h
  types/OcppChargingProfile.h
  types/OcppChargingProfile.cpp
  types/ConfigurationKeys.h
  confs/UnknownKeys.h
  types/OcppMeasurand.h
  types/OcppMessage.h
  types/OcppMessageType.h
  types/OcppMeterValue.h
  types/OcppMeterValue.cpp
  types/OcppSampledValue.h
  types/OcppSampledValue.cpp
  utils/chrono.h
  utils/chrono.cpp
  types/ConfigurationKey.h
  OcppService.h
  OcppService.cpp
  confs/OcppConfField.h
  OcppConfParser.h OcppConfParser.cpp
  Emitter.h
  Emitter.cpp
  OcppReqParser.h OcppReqParser.cpp
  reqs/BootNotification.h reqs/BootNotification.cpp
  reqs/OcppReq.h
  reqs/StatusNotification.h
  reqs/StatusNotification.cpp
  reqs/OcppReqBase.h
  reqs/OcppReqBase.cpp
  types/OcppChargePointErrorCode.h
  types/OcppChargePointStatus.h
  confs/UnknownKeys.h
  types/OcppUpdateStatus.h
  types/ConfigurationValue.h
)

target_include_directories(ocpp
PUBLIC
  ../
)

target_link_libraries(ocpp
PUBLIC
  deps
)
