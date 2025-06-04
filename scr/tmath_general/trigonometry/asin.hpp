#ifndef ASIN_HPP
#define ASIN_HPP
#include "sin.hpp"
#include <stdexcept>
#include "cos.hpp"
#include "../general/abs.hpp"
#include "../t_math_constant.hpp"
namespace t_math
{
    inline long double asin(double args)
    {
        if (abs(args) > 1)
            throw std::out_of_range("Asin only accept values between -1 and 1.");
        long double temp = 0;
        // sin(asin(t))-t=0
        while (abs(sin(temp) - args) > t_math_precise)
        {
            temp = temp - (sin(temp) - args) / cos(temp);
        };
        return temp;
    };
}
#endif // ASIN_HPP
