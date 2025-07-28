#pragma once
#include "../config/config.hpp"

namespace core {

class App {
public:
    explicit App(const config::Config& cfg);
    // Run main loop or process startup
    int run();
private:
    const config::Config& cfg_;
    void initLogger();
    void initLang();
    void showWelcome();

    // future: network init, peer setup, UI init, etc.
};

} // namespace core
