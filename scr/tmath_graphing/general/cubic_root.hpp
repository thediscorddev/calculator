#ifndef CUBIC_ROOT_HPP
#define CUBIC_ROOT_HPP
#include "nthroot.hpp"
#include <stdexcept>
namespace t_math
{
    inline long double cubic_root(double x)
    {
        if (x < 0)
            return -1 * cubic_root(-1 * x);
        return root(x, 3);
    };
}
#endif