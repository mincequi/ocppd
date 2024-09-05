add_library(ocpp STATIC
  OcppActionHandler.h
  OcppActionType.h
  OcppCall.cpp
  OcppCallPayloadKey.h
  OcppCallResultPayloadKey.h
  OcppCallResultStatus.h
  OcppCallResult.h
  OcppCallResult.cpp
  OcppCallResultGenerator.h
  OcppCallResultGenerator.cpp
  OcppMessageParser.cpp
  OcppMessageType.h
  action/OcppAction.cpp
  action/OcppAction.h
  action/OcppActionBootNotification.h
  action/OcppActionBootNotification.cpp
)

target_include_directories(ocpp
PUBLIC
  ../
)

target_link_libraries(ocpp
PUBLIC
  deps
)
