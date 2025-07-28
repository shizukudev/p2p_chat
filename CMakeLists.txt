cmake_minimum_required(VERSION 3.15)  # Set minimum required CMake version
project(p2p_chat LANGUAGES CXX)       # Define project name and language

# -- Project‑wide compile options ------------------------------------------------

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create interface targets for warnings and common options
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)

add_library(project_options INTERFACE)
target_compile_options(project_options INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# -- Add submodules ----------------------------------------------------------------

# Each module directory has its own CMakeLists and builds a static library
add_subdirectory(config)
add_subdirectory(core)
add_subdirectory(lang)

# -- Build the main executable ----------------------------------------------------

add_executable(p2p_chat main.cpp)

# Link with project options and module libraries
target_link_libraries(p2p_chat
  PRIVATE
    project_warnings
    project_options
    config_lib       # from config/
    app_lib          # from core/
    lang_lib         # from lang/
)

# Add include directory for public headers
target_include_directories(p2p_chat
  PRIVATE
    ${PROJECT_SOURCE_DIR}/inc
)

# Specify C++ standard requirement
target_compile_features(p2p_chat PUBLIC cxx_std_17)
