#ifndef T_MATH_HPP
#define T_MATH_HPP
#define T_MATH_HPP_VERSION 1.0
// constant
#include "t_math_constant.hpp"
// general
#include "general/factorial.hpp"
#include "general/pow.hpp"
#include "general/floor.hpp"
#include "general/ceil.hpp"
#include "general/round_high.hpp"
#include "general/round_low.hpp"
#include "general/round.hpp"
#include "general/abs.hpp"
#include "general/exp.hpp"
#include "general/ln.hpp"
#include "general/nthroot.hpp"
#include "general/sqrt.hpp"
#include "general/cubic_root.hpp"
#include "general/log.hpp"
#include "general/d_pow.hpp"
// trigonometry
#include "trigonometry/sin.hpp"
#include "trigonometry/cos.hpp"
#include "trigonometry/tan.hpp"
#include "trigonometry/cot.hpp"
#include "trigonometry/sec.hpp"
#include "trigonometry/csc.hpp"
#include "trigonometry/asin.hpp"
#include "trigonometry/acos.hpp"
#include "trigonometry/atan.hpp"
#include "trigonometry/acot.hpp"
#include "trigonometry/asec.hpp"
#include "trigonometry/acsc.hpp"
// hyperbolic
#include "hyperbolic/sinh.hpp"
#include "hyperbolic/cosh.hpp"
#include "hyperbolic/tanh.hpp"
#include "hyperbolic/coth.hpp"
#include "hyperbolic/sech.hpp"
#include "hyperbolic/csch.hpp"
#include "hyperbolic/asinh.hpp"
#include "hyperbolic/acosh.hpp"
#include "hyperbolic/atanh.hpp"
#include "hyperbolic/acoth.hpp"
#include "hyperbolic/asech.hpp"
#include "hyperbolic/acsch.hpp"
/*
Special functions
These functions aren't elementary, but what makes them appear here is that they show up often enough to have a name.
*/
#include "special/si.hpp"
#include "special/ci.hpp"
#include "special/gamma.hpp"
#include "special/erf.hpp"
#include "special/erfi.hpp"
#include "special/erfc.hpp"
#include "special/zeta.hpp"
#include "special/li.hpp"
#include "special/shi.hpp"
#include "special/ProductLog.hpp"
#include "special/ProductLogAlternativeBranch.hpp"
#include "special/EulerTotient.hpp"
//other function
#include "other/is_int.hpp"
#include "other/gcd.hpp"
#include "other/lcm.hpp"
#endif // T_MATH_HPP
