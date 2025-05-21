//
//  regexp.cpp
//  algorithms
//
//  Created by Igor on 21.05.2025.
//

#include <stdio.h>
#include <regex>
#include <string>

bool isBinaryBy3Dividing(std::string text) {
    std::regex r("^(0|1(01*0)*1)*$");
    return regex_match(text, r);
}
