#ifndef POW_HPP
#define POW_HPP
#include <stdexcept>
namespace t_math
{
    inline long double pow_int(double base, int exponent)
    {
        if (exponent == 0)
            return 1.0;
        if (exponent < 0)
            return 1.0 / pow_int(base, -exponent);

        long double result = 1.0;
        long double current = base;
        int exp = exponent;

        while (exp > 0)
        {
            if (exp & 1)
                result *= current;
            current *= current;
            exp >>= 1;
        }
        return result;
    }
};
#endif // POW_HPP
