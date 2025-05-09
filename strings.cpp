//
//  strings.cpp
//  algorithms
//
//  Created by Igor on 05.05.2025.
//

#include "strings.hpp"
#include "numbers.hpp"
#include <string>
#include <cctype>
#include <sstream>
#include <format>
#include <regex>
#include <iostream>

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

std::string duplicate_encoder(const std::string& word){
    std::string r = "";
    int map[128] = {};
    for (auto &c : word) map[tolower(c)]++;
    for (auto &c : word) r += map[tolower(c)] > 1 ? ")" : "(";
    return r;
}

/**
 Adds two integers and returns binary string as result
 **/
std::string add_binary(uint64_t a, uint64_t b) {
    std::vector<uint64_t> stack;
    convertToBinary(a + b, stack);
    std::string result;
    for(const uint64_t& i : stack)
        result += std::to_string(i);
    return result;
}

std::string add_binary_bp1(std::uint64_t a, std::uint64_t b) {
  return std::format("{:b}", a + b);
};

std::string add_binary_bp2(uint64_t a, uint64_t b) {
    a += b;
    std::string output;

    do {
        output = std::to_string(a % 2) + output;
        a /= 2;
    } while(a > 0);

    return output;
};

std::string to_camel_case(std::string text) {
    std::regex re("[_\-][A-Za-z]");
    std::smatch match;
    std::string result;
    for (std::smatch sm; std::regex_search(text, sm, re); text = sm.suffix()) {
        result += sm.prefix();
        result += std::toupper(std::string(sm[0])[1]);
    }
    result += text;
    return result;
}

std::string to_camel_case_bp(std::string s)
{
    for(int i{0}; i < s.size(); ++i)
        if(s[i] == '-' || s[i] == '_')
            s.erase(i, 1), s[i] = toupper(s[i]);
    return s;
}
