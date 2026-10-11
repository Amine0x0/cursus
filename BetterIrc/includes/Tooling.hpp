#ifndef TOOLING_HPP
#define TOOLING_HPP

#include <iostream>
#include <string>
#include <vector>

struct Color {
    static const char* const reset;
    static const char* const red;
    static const char* const green;
    static const char* const yellow;
    static const char* const purple;
    static const char* const cyan;
};

enum LogType {
    LOG_ERROR,  
    LOG_INFO,   
    LOG_SUCCESS,
    LOG_DEV,
};

namespace tooling {
    void PrettyLog(const LogType type, const std::string& msg);
    std::string toLower(const std::string& text);
    std::string toUpper(const std::string& text);

    std::string toString(size_t value);

    std::vector<std::string> split(const std::string& text, char separator);
}

std::string getCurrentTimestamp();
void PrintAsciiBanner();

#endif
