#ifndef TAN_HPP
#define TAN_HPP
#include "sin.hpp"
#include "cos.hpp"
namespace t_math
{
    inline double tan(double args)
    {
        return sin(args) / cos(args);
    };
};
#endif // TAN_HPP
