#ifndef ACOS_HPP
#define ACOS_HPP
#include "asin.hpp"
#include "../t_math_constant.hpp"
#include "../general/abs.hpp"
#include <stdexcept>
namespace t_math
{
    inline long double acos(double args)
    {
        if (abs(args) > 1)
            throw std::out_of_range("Acos only accept values between -1 and 1.");
        return pi / 2 - asin(args);
    }
}
#endif // ACOS_HPP
