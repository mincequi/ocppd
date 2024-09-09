cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# set c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add DEBUG definition for debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# create project
project(ocppd)

# add dependencies
include(cmake/CPM.cmake)

add_subdirectory(src/deps)
add_subdirectory(src/ocpp)
add_subdirectory(webapp)
add_subdirectory(tests)

# add executable
add_executable(ocppd
  main.cpp
  src/ApiClientRepository.h
  src/ApiClientRepository.cpp
  src/ApiRoute.h
  src/ApiRoute.cpp
  src/CallHandler.cpp
  src/ChargePointFactory.h
  src/ChargePointFactory.cpp
  src/ChargePointRepository.h
  src/ChargePointRepository.cpp
  src/ChargePoint.h
  src/ChargePoint.cpp
  src/OcppRoute.h
  src/OcppRoute.cpp
  src/Properties.h
  src/ResourceRoute.h src/ResourceRoute.cpp
  src/utils/Overload.h
  src/CallResultHandler.h src/CallResultHandler.cpp
  src/ConfigurationRepository.h src/ConfigurationRepository.cpp
)

target_link_libraries(ocppd
PUBLIC
  ocpp
  webapp
)
