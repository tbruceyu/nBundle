#include "Log.h"


android_LogPriority Log::minLevel = ANDROID_LOG_DEFAULT;

void Log::setLevel(android_LogPriority level) {
    Log::minLevel = level;
}