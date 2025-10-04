#pragma once

#include "snowhouse/assert.h"
#include "snowhouse/snowhouse.h"
#include "square-into-squares.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace snowhouse;

void printVector(std::vector<int> vec) {
  for (auto &it: vec) {
    std::cout << it << ",";
  }
  std::cout << "\n";
}

std::vector<int> getLargestSequence(std::vector<std::vector<int>> &seqs) {
  assert(seqs.size() > 0 && "no sequence to process");
  if (seqs.size() == 1) {
    return seqs[0];
  }
  std::vector<int> largest_sequence = seqs[0];
  for (int i = 1; i < seqs.size(); i++) {
    int lookup_value_largest = 0;
    int lookup_value_current = 0;
    int lookup_index = 1;
    while(lookup_value_current == lookup_value_largest) {
      try {
        lookup_value_largest += largest_sequence.at(largest_sequence.size() - lookup_index);
        lookup_value_current += seqs[i].at(seqs[i].size() - lookup_index);
        lookup_index++;
      } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        break;
      }
    }
    if (lookup_value_current > lookup_value_largest) {
      largest_sequence = seqs[i];
    }
  }
  return largest_sequence;
}

std::vector<int> inverseVector() {
  
}

void testDecompose(int input, std::vector<int> expected_result) {
  std::vector<int> result = decompose(input);
  printVector(result);

  AssertThat(result, Is().EqualTo(expected_result));

  std::cout << "Test OK" << "\n";
}

int main(int argc, char **argv)
{
  testDecompose(11, std::vector<int>{ 1, 2, 4, 10 });
  testDecompose(50, std::vector<int>{ 1, 3, 5, 8, 49 });
}
