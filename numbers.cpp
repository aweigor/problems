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
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <format>
#include <numeric>

#define ull unsigned long long

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

std::string uint32_to_ip(uint32_t ip)
{
    std::string v4Address;
    for (int i = 4; i > 0; --i) {
        v4Address = std::to_string(ip % 256) + '.' + v4Address;
        ip /= 256;
    }
    v4Address.pop_back();
    return v4Address;
}

union IP
{
    uint32_t ip;
    unsigned char arr[4];
};

std::string uint32_to_ip_clever(uint32_t ip)
{
    IP adress{ ip };
    std::string str{};
    for (int i = 3; i > 0; i--)
    str += std::to_string(adress.arr[i]) + ".";
    str += std::to_string(adress.arr[0]);

    return str;
}

std::string uint32_to_ip_super_clever(uint32_t ip)
{
  std::stringstream result{};
  result << (ip >> 24) << '.' << (ip >> 16 & 0xFF) << '.'
      << (ip >> 8 & 0xFF ) << '.' << (ip & 0xFF);
  return result.str();
}

std::string digit_to_hex(int digit, std::string result = "")
{
    static const char* numbers = "0123456789ABCDEF";
    if (digit != 0)
        result = digit_to_hex(digit / 16, result);
    return result + numbers[digit % 16];
}

std::string pad(std::string str, int w)
{
    if (str.size() > w)
        return str.substr(str.size() - w);
    std::stringstream ss;
    ss << std::setw(w) << std::setfill('0') << str;
    return ss.str();
}

int limit(int num, int from, int to) {
    return num < from ? from : num > to ? to : num;
}

std::string rgb_to_hex(int r, int g, int b)
{
    std::stringstream result{};
    result <<   pad(digit_to_hex(limit(r, 0, 255)), 2) <<
                pad(digit_to_hex(limit(g, 0, 255)), 2) <<
                pad(digit_to_hex(limit(b, 0, 255)), 2);
    return result.str();
}


class RGBToHex {
public:
  static std::string rgb(int r, int g, int b) {
    using namespace std;
    for(int& c : { ref(r), ref(g), ref(b) }) {
         c = max(0, min(255, c));
    }
    
    ostringstream oss;
    oss << uppercase << hex << setfill('0')
        << setw(6) << (r << 16) + (g << 8) + b;
    
    return oss.str();
  }
};

std::string rgb_to_hex_bp(int r, int g, int b)
{
    return std::format("{:02X}{:02X}{:02X}", std::clamp(r, 0, 255), std::clamp(g, 0, 255), std::clamp(b, 0, 255));
}

std::vector<uint32_t> find_pentagonals(uint32_t max_n) {
    std::vector<uint32_t> result{1, 2};
    int i = 2;
    while (result.back() < max_n) {
        result.push_back(i * (3 * i - 1) / 2);
        result.push_back(-i * (3 * -i - 1) / 2);
        i++;
    }
    return result;
}

typedef std::pair<int, uint32_t> part_n;
uint32_t find_partitions(uint32_t n, std::vector<uint32_t> const &pentagonal) {
    static std::vector<part_n> partitions{{0, 1}};
    if (n < 0)
        return 1;
    uint32_t result = 0;
    for (int i = 0; pentagonal[i] <= n; i++) {
        int pn = n - pentagonal[i];
        int pk = i % 4  > 1 ? -1 : 1;
        auto it = std::find_if(partitions.begin(), partitions.end(),
                      [&](const part_n& pair) { return pair.first == pn; });
        if (it == partitions.end()) {
            uint32_t p = find_partitions(pn, pentagonal);
            partitions.push_back({pn, p});
            result += pk * p;
        } else {
            result += pk * (*it).second;
        }
    }
    return result;
}

uint32_t partitions(uint32_t n) {
    std::vector<uint32_t> pentagonal = find_pentagonals(n);
    uint32_t result = find_partitions(n, pentagonal);
    return result;
}

uint32_t partitions_approx(uint32_t n) {
    uint32_t result = 1 / (4 * n * sqrt(3)) * exp(M_PI * sqrt((2 * n) / 3));
    return result;
}
/**
uint32_t partitions_min1(uint32_t n) {
   std::vector<unsigned long long int> vector(n + 1, 0);

 
    vector[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            vector[j] += vector[j - i];
        }
    }

    return vector[n];
}

uint32_t partitions_min3(uint32_t n) {
    std::vector<int> partitions(n + 1, 0);
    partitions[0] = 1;

    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            partitions[j] += partitions[j - i];

    return partitions[n];
}


uint32_t partitionsRev(uint32_t n, uint32_t k) {
    if(n==1 || k==1)  return 1;
    
    if(n<=k)  return partitionsRev(n,n-1)+1;
    
    return partitionsRev(n,k-1)+partitionsRev(n-k,k);
    }


uint32_t partitions_min2(uint32_t n) {
    return partitionsRev(n, n);
}
**/
/**
vector<uint32_t> pentagonals;

uint32_t pentagonal(uint32_t n) {
  if (n >= pentagonals.size()) {
    for (uint32_t i = pentagonals.size(); i <= n; ++i) {
      int32_t k = (i + 1) / 2;
      if (i % 2 == 0) {
        k = -k;
      }
      pentagonals.push_back((3 * k * k - k) / 2);
    }
  }
  return pentagonals[n];
}

vector<uint32_t> ps{1, 1};

uint32_t partitions(uint32_t n) {
  if (n >= ps.size()) ps.resize(n + 1, 0);
  if (ps[n] == 0) {
    int32_t res = 0;
    for (uint32_t i = 1; i <= n; ++i) {
      auto pent = pentagonal(i);
      auto prev = ((int32_t) n) - ((int32_t) pent);
      if (prev < 0) break;
      int32_t p = partitions(prev);
      if (i % 4 == 0 || i % 4 == 3) {
        p = -p;
      }
      res += p;
    }
    ps[n] = res;
  }
  return ps[n];
}
**/


bool isPrime(int num) {
    if (num % 2 == 0)
      return false;
    int n = num / 2;
    int m = n / 2;
    for (int i = n; i > m; --i) {
        int f = i;
        while (f != 1 && f % 2 != 0) {
            if (num % f == 0) {
                return false;
            }
            f /= 2;
        }
    }
    return true;
}


bool isPrime6(int num) {
    if (num == 2 || num == 3 || num == 5)
        return true;
    if (num <= 1 || num % 2 == 0 || num % 3 == 0 || num % 5 == 0)
        return false;
    int p5, p1;
    int maxn = sqrt(num) / 6;
    for (int i = 1; i <= maxn; i++) {
        p1 = i * 6 + 1;
        p5 = i * 6 + 5;
        if (num % p1 == 0 || num % p5 == 0)
            return false;
    }
    return true;
}

void seal(std::vector<unsigned long long>& arr, size_t i) {
    if (i < 0 || i > arr.size())
        return;
    unsigned long long x = arr[i];
    while (i > 0 && arr[i - 1] > x) {
        arr[i] = arr[i - 1]; --i;
    }
    arr[i] = x;
}



unsigned long long smallest_sum(const std::vector<unsigned long long>& arr)
{
    std::vector<unsigned long long> copy(arr);
    
    size_t s = copy.size();
    size_t i = 0;
    
    if (s == 1) return copy[0];
    if (s == 0) return 0;
    
    while (i < s - 1)
    {
        seal(copy, ++i);
    }
    
    while(i > 0)
    {
        if (copy[i - 1] == 0)
            break;
        if (copy[i] > copy[i - 1]) {
            copy[i] = copy[i] - copy[i - 1];
            seal(copy, i);
            i = s - 1;
        } else {
            --i;
        }
    }
    
    return std::reduce(copy.begin(), copy.end());
}

ull gcd(ull a, ull b){
    if (a==0)
        return b;
    return gcd(b%a,a);
}

ull smallest_sum_solution(const std::vector<ull>& arr){
    /*
    Basic trick to the problem is to identify that
    the smallest number you have at the end of all
    transformations is nothing but the GCD of all
    numbers. Since that number is repeated for each
    element in the array multiplying it by the size gets
    the right answer.
    
    Here is a reference: https://en.wikipedia.org/wiki/Greatest_common_divisor
    */
    int size = arr.size();
    ull result = arr[0];

    for (ull x : arr){
        result = gcd(x,result);
    }
    
    return size * result;
}
