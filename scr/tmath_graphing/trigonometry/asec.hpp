#ifndef ASEC_HPP
#define ASEC_HPP
#include "acos.hpp"
#include "../general/abs.hpp"
#include <stdexcept>
namespace t_math {
    inline double asec(double args) {
        if(abs(args) < 1) throw std::out_of_range("Asec only accept values between that is smaller or equal to -1 or bigger or equal to 1");
        return acos(1/args);
    };
}
#endif // ASEC_HPP