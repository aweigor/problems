#!/bin/sh
clang++ -Wall -std=c++17 string-ends-with.cpp -o a.out
chmod +x a.out
./a.out
rm a.out
