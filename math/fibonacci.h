#include <vector>

/**
 * TODO: description
 */

typedef unsigned long long ull;
class ProdFib
{
public:
    static std::vector<ull> productFib(ull prod);
    static std::vector<ull> productFibBp(ull prod)
    {
        ull a = 0, b = 1;
        while (a * b < prod) {
            std::swap(a, b);
            b += a;
        }
        return {a, b, ((a*b == prod) ? true : false)};
    }
};


std::vector<ull> ProdFib::productFib(ull prod) {
    ull f0 = 0;
    ull f1 = 1;
    ull f2 = f0 + f1;
    ull f3 = f1 + f2;
    while (f2 * f3 < prod) {
        f0 = f1;
        f1 = f2;
        f2 = f0 + f1;
        f3 = f1 + f2;
    }
    return std::vector<ull> {f2, f3, f2 * f3 == prod};
}
