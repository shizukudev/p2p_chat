#pragma once

#include <string>
#include <unordered_map>

namespace lang {

class LangManager {
public:
    // Load language file, e.g. "zh_CN" maps to lang/zh_CN.lang
    static bool load(const std::string& langCode, const std::string& langDir = "lang");

    // Fetch translation by key; returns key if missing
    static std::string tr(const std::string& key);

    // Get current language code
    static std::string current();
};
} // namespace lang
