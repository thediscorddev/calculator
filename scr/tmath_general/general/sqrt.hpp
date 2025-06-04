#ifndef SQRT_HPP
#define SQRT_HPP
#include "nthroot.hpp"
#include <stdexcept>
namespace t_math
{
    inline long double sqrt(double x)
    {
        if (x < 0)
            throw std::out_of_range("Sqrt of a negative number.");
        return root(x, 2);
    };
}
#endif