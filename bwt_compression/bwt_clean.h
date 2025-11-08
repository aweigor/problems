#pragma once

#include <utility>
#include <string>
#include <vector>

std::pair<std::string, int> encode_clean(const std::string& s) {
  std::vector<std::string> v;
  for (int i = 0; i < s.length(); i++) {
    v.push_back(s.substr(s.length() - i, i) + s.substr(0, s.length() - i));
  }
  std::sort(v.begin(), v.end());
    
  std::string str;
  for (int i = 0; i < v.size(); i++) {
    str.push_back(v[i][s.length() - 1]);
  }
  int r = std::find(v.begin(), v.end(), s) - v.begin();
  
  return std::make_pair(str, r);
}

std::string decode_clean(const std::string& s, int n) {
  if (s == "") 
    return "";
  
  std::vector<std::string> v(s.length(), "");
  for (int i = 0; i < s.length(); i++) {
    for (int j = 0; j < s.length(); j++) {
      v[j].insert(0, 1, s[j]);
    }
    std::sort(v.begin(), v.end());
  }
  return v[n];
}