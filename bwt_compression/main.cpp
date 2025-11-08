#include "../snowhouse/snowhouse.h"
#include "bwt.h"
#include <vector>
#include <string>
#include <iostream>

using namespace snowhouse;

void test1() {
  std::string rawText = "bananabar";
  std::string expectedResult = "nnbbraaaa";
  std::string encoded = bwt(rawText);
  std::string decoded = inverse_bwt(encoded);
  
  std::cout << "encoded: " << encoded << "\n";
  std::cout << "decoded: " << decoded << "\n";

  //AssertThat(encoded, Is().EqualTo(expectedResult));
  //AssertThat(decoded, Is().EqualTo(rawText));

}

int main(int argc, char **argv)
{
  test1();
}
