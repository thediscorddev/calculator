#ifndef COT_HPP
#define COT_HPP
#include "sin.hpp"
#include "cos.hpp"
namespace t_math
{
    inline double cot(double args)
    {
        return cos(args) / sin(args);
    };
};
#endif // COT_HPP
