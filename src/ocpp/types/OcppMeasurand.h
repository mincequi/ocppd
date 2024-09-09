#pragma once

namespace ocpp::types {

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
    Voltage,                        // V
    Frequency,                      // Hz
    SoC,                            // %
    Temperature                     // °C
};

} // namespace ocpp::types
