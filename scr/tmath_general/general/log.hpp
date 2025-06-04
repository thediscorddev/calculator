#ifndef LOG_HPP
#define LOG_HPP
#include <cstdint>
namespace t_math
{
    inline double lb_fast(double args)
    {
        if (args <= 0)
            throw std::domain_error("log2 domain error");
        union
        {
            double d;
            uint64_t i;
        } u = {args};
        int exponent = ((u.i >> 52) & 0x7FF) - 1023;
        u.i &= ~(0x7FFULL << 52);      // clear exponent
        u.i |= (uint64_t)(1023) << 52; // set exponent to 0 -> [1,2)
        double b = u.d;
        double y = (b - 1) / (b + 1);
        constexpr double inv_ln2 = 1.44269504089;

        double log2b = inv_ln2 * (y +
                                  y * y * y / 3 + y * y * y * y * y / 5 + y * y * y * y * y * y * y / 7 + y * y * y * y * y * y * y * y * y / 9 + y * y * y * y * y * y * y * y * y * y * y / 11);

        return exponent + log2b;
    }
    inline double log(double base, double args)
    {
        return lb_fast(args) / lb_fast(base);
    };
    inline double log(double args)
    {
        return log(10, args);
    };
    inline double lb(double args)
    {
        return log(2, args);
    };
};
#endif // LOG_HPP