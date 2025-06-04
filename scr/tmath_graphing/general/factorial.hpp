#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP
#include <stdexcept>
namespace t_math
{
    inline long double d_fac(int args)
    {
        if (args < 0)
            throw std::out_of_range("Factorial only accepts positive integer.");
        if (args <= 1)
            return 1;
        return args * d_fac(args - 1);
    };
    inline long long int fac(int args)
    {
        if (args < 0)
            throw std::out_of_range("Factorial only accepts positive integer.");
        if (args <= 1)
            return 1;
        return args * fac(args - 1);
    };
};
#endif // FACTORIAL_HPP
