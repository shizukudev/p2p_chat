#include "lang_manager.hpp"
#include "../core/logger.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace lang {

static std::unordered_map<std::string, std::string> translations;
static std::string currentLang = "en_US";

static inline std::string trim(const std::string& s) {
    const char* ws = " \t\n\r";
    auto l = s.find_first_not_of(ws);
    if (l == std::string::npos) return "";
    auto r = s.find_last_not_of(ws);
    return s.substr(l, r - l + 1);
}

bool LangManager::load(const std::string& langCode, const std::string& langDir) {
    translations.clear();
    currentLang = langCode;
    std::string path = langDir + "/" + langCode + ".lang";
    std::ifstream ifs(path);
    if (!ifs) {
        core::Logger::instance().error("LangManager: failed to open " + path);
        return false;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = trim(line.substr(0, pos));
        std::string val = trim(line.substr(pos + 1));
        translations[key] = val;
    }
    core::Logger::instance().info("Loaded language file: " + path + ", entries: " + std::to_string(translations.size()));
    return true;
}

// tr and current remain unchanged
std::string LangManager::tr(const std::string& key) {
    auto it = translations.find(key);
    return (it != translations.end() ? it->second : key);
}

std::string LangManager::current() {
    return currentLang;
}

} // namespace lang
