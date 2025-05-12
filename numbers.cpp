//
//  numbers.cpp
//  algorithms
//
//  Created by Igor on 06.05.2025.
//

#include "numbers.hpp"

#include <vector>
#include <cmath>
#include <string>

int square_digits(int num) {
    int result = 0;
    int remain = num;
    std::vector<int> stack;
    while (remain > 0) {
        stack.push_back(pow(remain % 10, 2));
        remain /= 10;
    }
    for (; !stack.empty(); stack.pop_back()) {
        result *= stack.back() > 10 ? 100 : 10;
        result += stack.back();
    }
    return result;
}

int square_digits_second(int num) {
    int result = 0;
    int mult = 1;
    while (num > 0) {
        int d = num % 10;
        result += mult * d * d;
        mult *= d > 3 ? 100 : 10;
        num /= 10;
    }
    return result;
}

int square_digits_third(int num) {
    std::string s = std::to_string(num);
    std::string ans;
    for(char c: s){
        int i = c - '0';
        ans += std::to_string(i * i);
    }
    return std::stoi(ans);
}

void convertToBinary(uint64_t n, std::vector<uint64_t> &s)
{
    if (n / 2 != 0) {
        convertToBinary(n / 2, s);
    }
    s.push_back(n % 2);
}

/**
 * https://projecteuler.net/problem=1
 * all numbers from 1 to 15 / 2 = all numbers that divides by 3 and 5
 * this idea not working yet, dont know why
 **/
int multiples35(int number)
{
    int remain = (number - 1) % 15;
    int base = (number - 1) - remain;
    int result = (1 + base) * base / 4;
    for (int i = remain; i >= 3; --i) {
        if (i % 5 == 0 || i % 3 == 0)
            result += base + i;
    }
    return result;
}

int multiples35_slow(int number)
{
    int result = 0;
    for (int i = number - 1; i >= 3; --i) {
        if (i % 5 == 0 || i % 3 == 0)
            result += i;
    }
    return result;
}

/**
 https://en.wikipedia.org/wiki/Gauss_sum
 **/
int solution_gauss(int number)
{
  int n = number - 1;
  return (3 * (n / 3) * ((n / 3) + 1) / 2) + (5 * (n / 5) * ((n / 5) + 1) / 2) - (15 * (n / 15) * ((n / 15) + 1) / 2);
}

int solution_gauss_2(int number)
{
  int threes, fives, fifteens;
  int sum_threes, sum_fives, sum_fifteens;
  threes = (number - 1) / 3;
  fives = (number - 1) / 5;
  fifteens = (number - 1)/ 15;
  sum_threes = 3 * (threes * (threes + 1)) / 2;
  sum_fives = 5 * (fives * (fives + 1)) / 2;
  sum_fifteens = 15 * (fifteens * (fifteens + 1)) / 2;
  return sum_threes + sum_fives - sum_fifteens;
}
