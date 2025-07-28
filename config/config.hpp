#pragma once

#include <string>
#include "../core/logger.hpp"
#include "cxxopts.hpp"

namespace config {

struct Config {
    std::string lang = "en_US";
    int listenPort = 9000;
    bool enableNat = false;
    core::LogLevel logLevel = core::LogLevel::INFO;
};

class ConfigParser {
public:
    // Parses command-line arguments and returns a Config instance
    static Config parse(int argc, char* argv[]);
};

} // namespace config
