#pragma once

#include <string>
#include <sstream>

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

std::string uint32_to_ip_best_practice(uint32_t ip)
{
    IP adress{ ip };
    std::string str{};
    for (int i = 3; i > 0; i--)
    str += std::to_string(adress.arr[i]) + ".";
    str += std::to_string(adress.arr[0]);

    return str;
}

std::string uint32_to_ip_clever(uint32_t ip)
{
  std::stringstream result;
  result << (ip >> 24) << '.' << (ip >> 16 & 0xFF) << '.'
      << (ip >> 8 & 0xFF ) << '.' << (ip & 0xFF);
  return result.str();
}