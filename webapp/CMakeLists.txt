CPMAddPackage("gh:vector-of-bool/cmrc#952ffdd")

include(${cmrc_SOURCE_DIR}/CMakeRC.cmake)

cmrc_add_resource_library(webapp WHENCE build/web
  build/web/favicon.png
  build/web/flutter_bootstrap.js
  build/web/flutter_service_worker.js
  build/web/index.html
  build/web/main.dart.js
  build/web/manifest.json
  build/web/assets/AssetManifest.json
  build/web/assets/FontManifest.json
  build/web/assets/fonts/MaterialIcons-Regular.otf
  build/web/icons/Icon-192.png
)

# Make sure the build depends on the Flutter build
add_dependencies(webapp build_webapp)

# Specify the Flutter source files that should trigger a rebuild
file(GLOB_RECURSE FLUTTER_SOURCES
  ${CMAKE_SOURCE_DIR}/webapp/pubspec.yaml
  ${CMAKE_SOURCE_DIR}/webapp/lib/*.dart
  ${CMAKE_SOURCE_DIR}/webapp/web/*.html
  ${CMAKE_SOURCE_DIR}/webapp/web/*.js
)

# Add a custom command to build the Flutter web app
add_custom_command(
OUTPUT ${CMAKE_SOURCE_DIR}/webapp/build/web
COMMAND flutter build web --release --web-renderer html
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/webapp
DEPENDS ${FLUTTER_SOURCES}
COMMENT "Building web app..."
VERBATIM
)

# Add a custom target that depends on the Flutter build
add_custom_target(build_webapp ALL
DEPENDS
  ${CMAKE_SOURCE_DIR}/webapp/build/web
)
