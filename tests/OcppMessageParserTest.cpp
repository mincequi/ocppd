#include <catch2/catch_all.hpp>

#include <ocpp/OcppCall.h>
#include <ocpp/OcppMessageParser.h>

const std::string message = R"([2,"531531554","MeterValues",
    {"connectorId":1,
     "meterValue":[{"timestamp":"2024-09-02T16:59:22.916Z",
                    "sampledValue":[{"value":"12.27",
                                     "measurand":"Current.Import",
                                     "unit":"A",
                                     "phase":"L1"},
                                    {"value":"0.00",
                                     "measurand":"Current.Import",
                                     "unit":"A",
                                     "phase":"L2"},
                                    {"value":"0.00",
                                     "measurand":"Current.Import",
                                     "unit":"A",
                                     "phase":"L3"},
                                    {"value":"13.00",
                                     "measurand":"Current.Offered",
                                     "unit":"A"},
                                    {"value":"2180918.72",
                                     "measurand":"Energy.Active.Import.Register",
                                     "unit":"Wh"},
                                    {"value":"49.94",
                                     "measurand":"Frequency"},
                                    {"value":"2589.05",
                                     "measurand":"Power.Active.Import",
                                     "unit":"W",
                                     "phase":"L1"},
                                    {"value":"0.00",
                                     "measurand":"Power.Active.Import",
                                     "unit":"W",
                                     "phase":"L2"},
                                    {"value":"0.00",
                                     "measurand":"Power.Active.Import",
                                     "unit":"W",
                                     "phase":"L3"},
                                    {"value":"2589.05",
                                     "measurand":"Power.Active.Import",
                                     "unit":"W"},
                                    {"value":"2990.00",
                                     "measurand":"Power.Offered",
                                     "unit":"W"}]}]}])";

using namespace ocpp;

// Sample test cases
TEST_CASE("Simple arithmetic") {
    OcppMessageParser parser;
    auto result = parser.parse(message);
    REQUIRE(std::holds_alternative<OcppCall>(result));
}
