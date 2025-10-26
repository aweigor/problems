#pragma once

#include <string>
#include <sstream>

std::string alphabet_position(const std::string &text) {
    std::string result = "";
    for(char c: text) {
        int pos = tolower(c) - 'a';
        if (pos >= 0 && pos < 26) { // std::isalpha
            if (result.length() > 0) {
                result += " ";
            }
            result += std::to_string(pos + 1);
        }
    }
    return result;
};

std::string alphabet_position_bp(const std::string &s) {
    std::stringstream ss;
    for (auto &x : s) if (std::isalpha(x)) ss << (x | 32) - 96 << ' ';
    std::string r = ss.str();
    if (r.size()) r.pop_back();
    return r;
}