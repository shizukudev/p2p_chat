#include "logger.hpp"
#include "portable_time.hpp"  // portable_localtime wrapper
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace core {

Logger& Logger::instance() {
    static Logger inst;
    return inst;
}

void Logger::init(const std::string& logFilePath, LogLevel level) {
    Logger& L = instance();
    L.logFile_.open(logFilePath, std::ios::app);
    L.minLevel_ = level;
    if (!L.logFile_.is_open()) {
        std::cerr << "Failed to open log file: " << logFilePath << std::endl;
    }
}

Logger::~Logger() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

void Logger::debug(const std::string& msg) { log(LogLevel::DEBUG, msg); }
void Logger::info(const std::string& msg)  { log(LogLevel::INFO, msg); }
void Logger::warning(const std::string& msg) { log(LogLevel::WARNING, msg); }
void Logger::error(const std::string& msg) { log(LogLevel::ERROR, msg); }

void Logger::log(LogLevel level, const std::string& msg) {
    if (level < minLevel_) return;

    auto now = std::time(nullptr);
    std::tm tm{};
    if (!portable_localtime(&now, &tm)) {
        // optional: fallback behavior, still proceed without timestamp
    }

    // Ensure enum / name mapping stays consistent
    static_assert(static_cast<int>(LogLevel::ERROR) == 3, "LogLevel mapping must remain synced");

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    const char* levelNames[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    std::string line = oss.str() + " [" + levelNames[static_cast<int>(level)] + "] " + msg;

    std::lock_guard<std::mutex> lk(mutex_);
    std::cout << line << std::endl;
    if (logFile_.is_open()) {
        logFile_ << line << std::endl;
        logFile_.flush();
    }
}

} // namespace core
