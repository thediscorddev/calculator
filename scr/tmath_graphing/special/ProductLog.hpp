#ifndef PRODUCTLOG_HPP
#define PRODUCTLOG_HPP
#include "../t_math_constant.hpp"
#include "../general/exp.hpp"
#include "../general/abs.hpp"
#include "../general/ln.hpp"
#include "../general/round.hpp"
#include <stdexcept>
namespace t_math 
{
    inline double ProductLog(double args) 
    {
        // The principal branch of the Lambert W function
        double temp = 1; // inital guess
        if(args == -1/e) return -1;
        if(args < -1/e)
            throw std::out_of_range("The principal branch of the Lambert W function is not defined for value that is lower than -1/e.");
        if(args == 0) 
            return 0; // no need to calculating
        if(args > e-0.189)
            temp = ln(args)/(1.18 * exp(0.018 * ln(args))); // First guess for larger values of args
        while(abs(temp * exp(temp) - args) > t_math_precise) // While the approximation isn't good enough
            temp -= (temp * exp(temp) - args)/(exp(temp) * (temp + 1));
        return temp;
    };
};
#endif // PRODUCTLOG_HPP