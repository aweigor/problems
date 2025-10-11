#pragma once

#include <algorithm>
#include <sstream>
#include <vector>
std::string bwt(std::string &s) 
{
  // create a table, where the rows are all possible rotations of s
  std::vector<std::string> matrix{};
  std::string shift;
  for (int i = 0; i < s.size(); i++) {
    shift = s;
    std::rotate(shift.begin(), shift.begin() + i, s.end());
    matrix.push_back(shift);
  }
  // sort rows alphabetically
  for (auto i = matrix.begin(); i != matrix.end(); ++i) {
    std::rotate(std::upper_bound(matrix.begin(), i, *i), i, i + 1);
  }
  // return last column of the table
  std::stringstream ss;
  for (auto i = matrix.begin(); i != matrix.end(); ++i) {
    ss << i->back();
  }
  return ss.str();
}
