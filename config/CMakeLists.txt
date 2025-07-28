# config/CMakeLists.txt
add_library(config_lib
    config.cpp
    config.hpp
)

# Expose include dir so config module can find cxxopts.hpp in inc/
target_include_directories(config_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/inc   # 添加这一行
)

target_link_libraries(config_lib PUBLIC
    project_warnings
    project_options
)
