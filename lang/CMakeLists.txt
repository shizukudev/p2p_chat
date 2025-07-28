# lang/CMakeLists.txt
add_library(lang_lib
  lang_manager.cpp
  lang_manager.hpp
)

# Expose lang headers to consumers
target_include_directories(lang_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/core   # Add this line
)

# Use warnings/options and optionally config_lib if needed
target_link_libraries(lang_lib PUBLIC
  project_warnings
  project_options
)
