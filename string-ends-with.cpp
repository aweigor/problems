#include <iostream>
#include <string>

bool solution(std::string const &str, std::string const &ending) {
  int i = static_cast<int>(str.length());
  int j = static_cast<int>(ending.length());
  if (i < j) {
    return false;
  }
  while (j > 0) {
    if (str[i - 1] != ending[j - 1]) {
      break;
    }
    i--;
    j--;
  }
  return j == 0;
}

int main(int argc, char *argv[]) {
  std::string a = "abcabc";
  std::string b = "abc";

  std::cout << solution(a, b) << "\n";
}
