//
//  strings.cpp
//  algorithms
//
//  Created by Igor on 05.05.2025.
//

#include "strings.hpp"
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

