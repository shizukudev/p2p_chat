#include "config.hpp"
#include <iostream>

namespace config {

Config ConfigParser::parse(int argc, char* argv[]) {
    cxxopts::Options options("p2p_chat", "P2P terminal chat application");

    options.add_options()
        ("h,help", "Show help")
        ("l,lang", "Language code (zh_CN, en_US)", cxxopts::value<std::string>()->default_value("en_US"))
        ("p,listen-port", "Listening port number", cxxopts::value<int>()->default_value("9000"))
        ("n,enable-nat", "Enable NAT traversal", cxxopts::value<bool>()->default_value("false"))
        ("v,verbose", "Verbose (DEBUG) logging", cxxopts::value<bool>()->default_value("false"))
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        std::exit(0);
    }

    Config cfg;
    cfg.lang = result["lang"].as<std::string>();
    cfg.listenPort = result["listen-port"].as<int>();
    cfg.enableNat = result["enable-nat"].as<bool>();
    cfg.logLevel = result["verbose"].as<bool>() ? core::LogLevel::DEBUG : core::LogLevel::INFO;

    return cfg;
}

} // namespace config
