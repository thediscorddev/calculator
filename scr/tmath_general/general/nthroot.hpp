#ifndef NTHROOT_HPP
#define NTHROOT_HPP
#include "exp.hpp"
#include "ln.hpp"
namespace t_math
{
    inline long double root(double x, double y)
    {
        return exp(1 / y * ln(x));
    };
};
#endif