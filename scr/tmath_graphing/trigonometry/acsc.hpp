#ifndef ACSC_HPP
#define ACSC_HPP
#include "asin.hpp"
#include "../general/abs.hpp"
#include <stdexcept>
namespace t_math {
    inline double acsc(double args) {
        if(abs(args) < 1) throw std::out_of_range("acsc only accept values between that is smaller or equal to -1 or bigger or equal to 1");
        return asin(1/args);
    };
}
#endif // ACSC_HPP