#ifndef ACOT_HPP
#define ACOT_HPP
#include "atan.hpp"
#include "../t_math_constant.hpp"
namespace t_math
{
    inline double acot(double args)
    {
        return pi / 2 - atan(args);
    };
};
#endif // ACOT_HPP