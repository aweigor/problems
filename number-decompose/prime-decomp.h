#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric>


class PrimeDecomp
{
public:
    static int find_factor(int num) {
        if (num == 2 || num == 3 || num == 5)
            return num; // is prime
        if (num % 2 == 0)
            return 2;
        if (num % 3 == 0)
            return 3;
        if (num % 5 == 0)
            return 5;
        int p5, p1;
        int maxn = sqrt(num) / 6;
        for (int i = 1; i <= maxn; i++) {
            p1 = i * 6 + 1;
            p5 = i * 6 + 5;
            if (num % p1 == 0)
                return p1;
            if (num % p5 == 0)
                return p5;
        }
        return num; // is prime
    }
    static std::string print_factor(int factor, int pow) {
        std::ostringstream ss;
        if (pow > 1) {
            ss << "(" << factor << "**" << pow << ")";
        } else {
            ss << "(" << factor << ")";
        }
        return ss.str();
    }
    static std::string make_result(std::vector<int> &list) {
        std::sort(list.begin(), list.end());
        int current = *list.begin();
        int pown = 1;
        std::ostringstream ss;
        std::string result("");
        for (int i = 1; i < list.size(); i++) {
            if (current != list[i]) {
                result += print_factor(current, pown);
                current = list[i];
                pown = 1;
            } else {
                pown += 1;
            }
        }
        result += print_factor(current, pown);
        return result;
    }
    static std::string factors(int lst) {
        std::vector<int> list{};
        while (true) {
            int factor = find_factor(lst);
            list.push_back(factor);
            if (factor == lst)
                break;
            lst /= factor;
        }
        return make_result(list);
    }
};