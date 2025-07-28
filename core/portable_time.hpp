#pragma once
#include <ctime>

// portable_localtime: thread-safe conversion from time_t to std::tm
inline bool portable_localtime(const std::time_t* t, std::tm* out) {
    if (!t || !out) return false;
#if defined(_MSC_VER) || defined(_WIN32)
    // Windows secure version
    return ::localtime_s(out, t) == 0;
#else
    // POSIX thread-safe version
    return localtime_r(t, out) != nullptr;
#endif
}
