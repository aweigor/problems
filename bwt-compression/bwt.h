#pragma once

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <system_error>
#include <vector>

std::string bwt(std::string &s) 
{
  s += EOF; // add 'EOF' character
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

std::string inverse_bwt(std::string &s)
{
  // create empty table
  std::vector<std::string> matrix{};
  // fill table with first letters of bwt string 
  for (auto &c: s) {
    matrix.push_back(std::string(1, c));
  }
  for (int i = 0; i < s.size(); ++i) {
    // sort rows alphabetically
    for (auto k = matrix.begin(); k != matrix.end(); ++k) {
      std::rotate(std::upper_bound(matrix.begin(), k, *k), k, k + 1);
    }
    // update table with first letters of bwt string;
    for (int j = 0; j < s.size(); ++j) {
      matrix[j] = s[j] + matrix[j];
    }
  }
  // find row which eds with 'EOF' character
  for (auto &row: matrix) {
    if (row.back() != EOF)
      continue;
    return row;
  }
  throw std::logic_error("unexpected error");
}
