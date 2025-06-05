//
//  calc_functions.cpp
//  algorithms
//
//  Created by Igor on 05.06.2025.
//

#include "calc_functions.hpp"
int id(int n) { return n; }
int zero (op func) { return func(0); }
int one  (op func) { return func(1); }
int two  (op func) { return func(2); }
int three(op func) { return func(3); }
int four (op func) { return func(4); }
int five (op func) { return func(5); }
int six  (op func) { return func(6); }
int seven(op func) { return func(7); }
int eight(op func) { return func(8); }
int nine (op func) { return func(9); }

op plus      (int n) { return [=](int m) { return m + n; }; }
op minus     (int n) { return [=](int m) { return m - n; }; }
op times     (int n) { return [=](int m) { return m * n; }; }
op divided_by(int n) { return [=](int m) { return m / n; }; }
