#ifndef D_POW_HPP
#define D_POW_HPP
#include "log.hpp"
#include <stdexcept>
namespace t_math
{
    inline double pow2_int(int n)
    {
        if (n < 0)
            return 1.0 / pow2_int(-n);

        if (n <= 63)
            return static_cast<double>(1ULL << n); // exact for small powers

        // For larger exponents, do exponentiation by squaring
        double result = 1.0;
        double base = 2.0;
        while (n > 0)
        {
            if (n & 1)
                result *= base;
            base *= base;
            n >>= 1;
        }
        return result;
    }
    inline long double pow(double base, double exponent)
    {
        double exp = exponent;
        if (base < 0)
            throw std::domain_error("base < 0");
        if (exp < 0)
            return 1 / pow(base, -exp);
        if (exp == 1)
            return base;
        if (base == 1)
            return 1;
        if (base != 2)
            exp *= lb_fast(base);
        // Now we are ready to approximate
        int intp = static_cast<int>(exp);
        double decp = exp - intp;
        double intexp = pow2_int(intp);
        const double ln2 = 0.69314718056;
        double x = ln2 * decp;
        double decexp = 1 + x + x * x / 2 + x * x * x / 6;
        return intexp * decexp;
    };
};
#endif // POW_HPP
