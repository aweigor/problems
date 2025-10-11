#include "snowhouse/snowhouse.h"
#include "bubble-sort.hpp"
#include <vector>

using namespace snowhouse;

template <typename T>
void printArray(const std::vector<T>& arr) {
    for (const T& element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
  std::vector<int> testNumbers = { 5, 7, 12, 5, 44, 2 };
  bubbleSort(testNumbers);
  AssertThat(testNumbers, Is().EqualTo(std::vector<int>{ 2, 5, 5, 7, 12, 44 }));
  std::cout << "Sorted array: " << "\n";
  printArray(testNumbers);
  std::cout << "Test OK" << "\n";
}
