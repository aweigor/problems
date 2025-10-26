#pragma once

#include <vector>
#include <string>
#include <format>


/**
 Adds two integers and returns binary string as result
 **/

void convertToBinary(uint64_t n, std::vector<uint64_t> &s)
{
    if (n / 2 != 0) {
        convertToBinary(n / 2, s);
    }
    s.push_back(n % 2);
}


std::string add_binary(uint64_t a, uint64_t b) {
    std::vector<uint64_t> stack;
    convertToBinary(a + b, stack);
    std::string result;
    for(const uint64_t& i : stack)
        result += std::to_string(i);
    return result;
}

std::string add_binary_bp1(std::uint64_t a, std::uint64_t b) {
  return std::format("{:b}", a + b);
};

std::string add_binary_bp2(uint64_t a, uint64_t b) {
    a += b;
    std::string output;

    do {
        output = std::to_string(a % 2) + output;
        a /= 2;
    } while(a > 0);

    return output;
};