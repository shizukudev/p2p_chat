#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>
#include <fstream>

namespace core {

// Defines log severity levels
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

// Singleton Logger: outputs to console and file
class Logger {
public:
    // Initialize log file and severity threshold
    static void init(const std::string& logFilePath, LogLevel level = LogLevel::INFO);

    // Access singleton logger
    static Logger& instance();

    // Logging APIs
    void debug(const std::string& msg);
    void info(const std::string& msg);
    void warning(const std::string& msg);
    void error(const std::string& msg);

private:
    Logger() = default;
    ~Logger();

    void log(LogLevel level, const std::string& msg);

    std::ofstream logFile_;
    LogLevel minLevel_{LogLevel::INFO};
    std::mutex mutex_;
};

} // namespace core

#endif // LOGGER_H
