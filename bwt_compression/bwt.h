#pragma once

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <system_error>
#include <vector>
#include <iostream>

std::string bwt(const std::string &s) 
{
  const char SENTINEL = '$'; // use $ as sentinel (lexicographically smallest)
  std::string input = s + SENTINEL; // add sentinel character
  // create a table, where the rows are all possible rotations of input
  std::vector<std::string> matrix{};
  for (size_t i = 0; i < input.size(); i++) {
    std::string shift = input;
    std::rotate(shift.begin(), shift.begin() + i, shift.end());
    matrix.push_back(shift);
  }
  // sort rows alphabetically
  std::sort(matrix.begin(), matrix.end());
  // return last column of the table (excluding sentinel from output)
  std::stringstream ss;
  for (const auto &row : matrix) {
    char lastChar = row.back();
    if (true) {
      ss << lastChar;
    }
  }
  std::cout << ss.str() << "\n";
  return ss.str();
}

std::string inverse_bwt(const std::string &s)
{
    int n = s.size();
    
    // Start with empty strings
    std::vector<std::string> table(n, "");
    
    // Reconstruct by repeatedly:
    // 1. Prepend the BWT column to each string
    // 2. Sort lexicographically
    for (int i = 0; i < n; i++) {
        // Prepend BWT characters
        for (int j = 0; j < n; j++) {
            table[j] = s[j] + table[j];
        }
        // Sort
        std::sort(table.begin(), table.end());
    }
    
    // Find the row that ends with '$' - that's our original string
    for (const auto& row : table) {
        if (!row.empty() && row.back() == '$') {
            // Remove the '$' at the end before returning
            return row.substr(0, row.size() - 1);
        }
    }
    
    throw std::logic_error("Original string not found");
}


