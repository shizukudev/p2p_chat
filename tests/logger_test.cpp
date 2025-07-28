// g++ -std=c++17 -pthread core/logger.cpp tests/logger_test.cpp -Icore -o logger_test

#include "../core/logger.hpp"

int main() {
    core::Logger::init("test.log", core::LogLevel::DEBUG);

    auto& log = core::Logger::instance();

    log.debug("This is a DEBUG message");
    log.info("Hello from INFO");
    log.warning("Warning example");
    log.error("Error occurred!");

    return 0;
}
