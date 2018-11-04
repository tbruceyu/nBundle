#pragma once

#include <iostream>
#include <string>
#include <stdarg.h>
#include <android/log.h>
#include <unistd.h>

using namespace std;

class Log {
private:
    static android_LogPriority minLevel;

public:
    static void setLevel(android_LogPriority level);

    static void v(const char *TAG, const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        ANDROID_LOG_VERBOSE >= minLevel && __android_log_vprint(ANDROID_LOG_VERBOSE, TAG, fmt, args);
        va_end(args);
    }

    static void d(const char *TAG, const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        ANDROID_LOG_DEBUG >= minLevel && __android_log_vprint(ANDROID_LOG_DEBUG, TAG, fmt, args);
        va_end(args);
    }

    static void i(const char *TAG, const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        ANDROID_LOG_INFO >= minLevel && __android_log_vprint(ANDROID_LOG_INFO, TAG, fmt, args);
        va_end(args);
    }

    static void w(const char *TAG, const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        ANDROID_LOG_WARN >= minLevel && __android_log_vprint(ANDROID_LOG_WARN, TAG, fmt, args);
        va_end(args);
    }

    static void e(const char *TAG, const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        ANDROID_LOG_ERROR >= minLevel && __android_log_vprint(ANDROID_LOG_ERROR, TAG, fmt, args);
        va_end(args);
    }
};
