//
//  cyphers.cpp
//  algorithms
//
//  Created by Igor on 23.05.2025.
//

#include "cyphers.hpp"
#include <cctype>

std::string rot13(const std::string& str) {
    std::string dec;
    int x;
    for (auto &c: str) {
        if (!std::isalpha(c)) {
            dec += c;
            continue;
        }
        int base = std::isupper(c) ? 65 : 97;
        x = (c - base) % 13;
        if (x == c - base)
            x += 13;
        x += base;
        dec += (char)x;
    }
    return dec;
}

char rot13c(const char c) {
  if (islower(c))
    return (c - 'a' + 13) % 26 + 'a';
  if (isupper(c))
    return (c - 'A' + 13) % 26 + 'A';
  return c;
}
