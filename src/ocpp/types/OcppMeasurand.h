#pragma once

namespace ocpp::types {

// Keep this in sync with dart enum OcppMeasurand
enum class OcppMeasurand {
    EnergyActiveImportRegister,     // Wh
    EnergyActiveExportRegister,     // Wh
    EnergyReactiveImportRegister,   // varh
    EnergyReactiveExportRegister,   // varh
    PowerActiveImport,              // W
    PowerActiveExport,              // W
    PowerReactiveImport,            // var
    PowerReactiveExport,            // var
    PowerOffered,                   // W
    CurrentImport,                  // A
    CurrentExport,                  // A
    CurrentOffered,                 // A
    VoltageL1,                      // V
    VoltageL2,                      // V
    VoltageL3,                      // V
    Frequency,                      // Hz
    SoC,                            // %
    Temperature                     // °C
};

} // namespace ocpp::types
