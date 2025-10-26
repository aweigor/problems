#pragma once

#include <vector>
#include <string>
#include <map>

std::map<char, unsigned> count(const std::string& string) {
    std::map<char, unsigned> result;
    for (auto &c: string)
        result[c] = result.find(c) != result.end() ? ++result[c] : 1;
    return result;
}

std::map<char, unsigned> count_bp(const std::string& string) {
  std::map<char, unsigned> r;
  for (const char& c: string) ++r[c];
  return r;
}