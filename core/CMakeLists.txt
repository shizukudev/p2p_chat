# core/CMakeLists.txt
add_library(app_lib
  app.cpp
  app.hpp
  logger.cpp
  logger.hpp
)

# Public include directory exposes core headers
target_include_directories(app_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependency: config_lib and compile option targets
target_link_libraries(app_lib PUBLIC
  config_lib         # to access configuration settings
  project_warnings
  project_options
)
