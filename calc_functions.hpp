//
//  calc_functions.hpp
//  algorithms
//
//  Created by Igor on 05.06.2025.
//

#ifndef calc_functions_hpp
#define calc_functions_hpp

#include <stdio.h>
#include <functional>

#endif /* calc_functions_hpp */
using op = std::function<int(int)>;
int id(int n);

int zero (op func = id);
int one  (op func = id);
int two  (op func = id);
int three(op func = id);
int four (op func = id);
int five (op func = id);
int six  (op func = id);
int seven(op func = id);
int eight(op func = id);
int nine (op func = id);

op plus      (int n);
op minus     (int n);
op times     (int n);
op divided_by(int n);
