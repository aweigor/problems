#include <utility>
#include <string>
#include <vector>

std::pair<std::string, int> encode_optimized(const std::string& s) {
  std::vector<int> order(s.size());
  for (auto i = 0; i < s.size(); i ++) order[i] = i;
  
  // sorting in-place, without rotations table.
  // information about all symbols in rotations already known - 
  // it is just input string starting from certatin postion
  std::sort(order.begin(), order.end(), [&] (auto x, auto y) {
    // searches first non-equal character
    for (auto i = 0; i < s.size(); i ++) {
      int j = (x + i) % s.size();
      int k = (y + i) % s.size();
      if      (s[j] < s[k]) return true;
      else if (s[j] > s[k]) return false;
    }
    return false;
  });
  
  std::string result = s;
  int number = 0;
  for (auto i = 0; i < s.size(); i ++) {
    int j = order[i];
    if (j == 0) number = i;
    result[i] = s[(j + s.size() - 1) % s.size()];
  } 
  return {result, number};
}

std::string decode_optimized(const std::string& s, int n) {
  std::string order = s;
  std::sort(order.begin(), order.end());
  
  std::vector<int> number(s.size());
  for (int i = 0; i < order.size(); i ++) {
    int begin = (i == 0 || order[i] != order[i-1]) ? 0 : number[i - 1] + 1;
    number[i] = s.find(order[i], begin);
  }
  
  std::string result;
  for (auto i = 0; i < s.size(); i ++) {
    result.push_back(order[n]);
    n = number[n];
  }
  
  return result;
}