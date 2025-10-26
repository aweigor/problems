#pragma once

#include "cmath"

class ASum
{
  public:
  static long long findNb(long long m);
};


long long ASum::findNb(long long m) {
    long long acc = 0, n = 0;
    for (n = 0; acc < m; ++n)
        acc += n * n * n;
    return acc == m ? n - 1 : -1;
};

static long long findNb_math(long long m)
{
    // https://en.wikipedia.org/wiki/Faulhaber%27s_formula
    // 1^3 + 2^3 + ... n^3 = [n*(n+1)/2] ^2 = m
    // => n = (1 + sqrt(1 + 8 * sqrt(m))) / 2
    auto sqrt_m = (long long)std::sqrt(m);
    if (sqrt_m * sqrt_m != m)
      return -1;
    
    auto det = 1 +  8 * sqrt_m;
    auto sqrt_det = (long long)std::sqrt(det);
    if (sqrt_det * sqrt_det != det)
      return -1;
    
    if (sqrt_det % 2 == 0)
      return -1;
    return (1 + sqrt_det) / 2 - 1;
}
