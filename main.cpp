#include "core/app.hpp"
#include "config/config.hpp"

int main(int argc, char* argv[]) {
    auto cfg = config::ConfigParser::parse(argc, argv);
    core::App app(cfg);
    return app.run();
}
