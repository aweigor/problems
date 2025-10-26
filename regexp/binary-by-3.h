#pragma once

#include <string>
#include <regex>

bool isBinaryBy3Dividing(std::string text) {
    std::regex r("^(0|1(01*0)*1)*$");
    return regex_match(text, r);
}