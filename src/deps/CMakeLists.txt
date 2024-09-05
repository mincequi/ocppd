CPMAddPackage("gh:CrowCpp/Crow@1.2.0")
CPMAddPackage("gh:Neargye/magic_enum@0.9.6")
CPMAddPackage("gh:nlohmann/json@3.11.3")
CPMAddPackage("gh:victimsnino/ReactivePlusPlus@2.1.1")

add_library(deps
INTERFACE
)

target_link_libraries(deps
INTERFACE
  Crow::Crow
  magic_enum::magic_enum
  nlohmann_json::nlohmann_json
  rpp
)

target_compile_definitions(deps
INTERFACE
  CROW_JSON_NO_ERROR_CHECK
)
