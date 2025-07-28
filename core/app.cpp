#include "app.hpp"
#include "logger.hpp"
#include "../lang/lang_manager.hpp"
#include <iostream>

namespace core {

App::App(const config::Config& cfg)
    : cfg_(cfg)
{}

int App::run() {
    initLogger();
    core::Logger::instance().info("Starting application");
    core::Logger::instance().info("Language code: " + cfg_.lang);
    core::Logger::instance().info("Listen port: " + std::to_string(cfg_.listenPort));

    initLang();
    showWelcome();

    // TODO: later integrate network, UI, message handling loops
    return 0;
}

void App::initLogger() {
    // ensure log directory exists? for now assume path
    core::Logger::init("log/session.log", cfg_.logLevel);
}

void App::initLang() {
    if (!lang::LangManager::load(cfg_.lang)) {
        core::Logger::instance().warning("Falling back to default language");
    }
}

void App::showWelcome() {
    std::string w = lang::LangManager::tr("welcome");
    std::cout << w << std::endl;
}

} // namespace core
