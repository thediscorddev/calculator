#ifndef COS_HPP
#define COS_HPP
#include "sin.hpp"
#include "../t_math_constant.hpp"
namespace t_math
{
    inline double cos(double args)
    {
        return sin(pi / 2 - args);
    }
}
#endif // COS_HPP
