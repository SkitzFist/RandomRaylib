#pragma once
#include "include/raylib.h"
#include <string>

namespace Log{
    static void info(const std::string& info){
        TraceLog(LOG_INFO, info.c_str());    
    }

    static void warning(const std::string& warning){
        TraceLog(LOG_WARNING, warning.c_str());
    }

    static void error(const std::string& error){
        TraceLog(LOG_ERROR, error.c_str());
    }

    static void point(const std::string& info, Vector2 point){
        std::string str = info + ": " + std::to_string(point.x) + "." + std::to_string(point.y);
        TraceLog(LOG_INFO, str.c_str());
    }
    
    static void point(const std::string& info, Vector2i point){
        std::string str = info + ": " + std::to_string(point.x) + "|" + std::to_string(point.y);
        TraceLog(LOG_INFO, str.c_str());
    }   
}
