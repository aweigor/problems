#include "../snowhouse/snowhouse.h"
#include "bwt.h"
#include "bwt_nosent.h"
#include <vector>
#include <string>
#include <iostream>

using namespace snowhouse;

void testSentinel() {
  std::string rawText = "bananabar";
  std::string expectedResult = "nnbbraaaa";
  std::string encoded = bwt(rawText);
  std::string decoded = inverse_bwt(encoded);
  
  std::cout << "encoded: " << encoded << "\n";
  std::cout << "decoded: " << decoded << "\n";

  AssertThat(encoded, Is().EqualTo(expectedResult));
  AssertThat(decoded, Is().EqualTo(rawText));
}

void testNoSentinel() {
  std::string rawText = "bananabar";
  std::string expectedResult = "nnbbraaaa";
  auto encoded = encode(rawText);
  std::string decoded = decode(encoded.first, encoded.second);
  
  std::cout << "encoded: " << encoded.first << "\n";
  std::cout << "decoded: " << decoded << "\n";

  AssertThat(encoded.first, Is().EqualTo(expectedResult));
  AssertThat(decoded, Is().EqualTo(rawText));


  rawText = "Humble Bundle";
  expectedResult = "e emnllbduuHB";
  encoded = encode(rawText);
  decoded = decode(encoded.first, encoded.second);
  
  std::cout << "encoded: " << encoded.first << "\n";
  std::cout << "decoded: " << decoded << "\n";

  AssertThat(encoded.first, Is().EqualTo(expectedResult));
  AssertThat(decoded, Is().EqualTo(rawText));


  rawText = "Mellow Yellow";
  expectedResult = "ww MYeelllloo";
  encoded = encode(rawText);
  decoded = decode(encoded.first, encoded.second);
  
  std::cout << "encoded: " << encoded.first << "\n";
  std::cout << "decoded: " << decoded << "\n";

  AssertThat(encoded.first, Is().EqualTo(expectedResult));
  AssertThat(decoded, Is().EqualTo(rawText));

  std::cout << "Test OK" << "\n";

}

int main(int argc, char **argv)
{
  testNoSentinel();
}