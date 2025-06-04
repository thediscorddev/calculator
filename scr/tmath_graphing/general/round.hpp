#ifndef ROUND_HPP
#define ROUND_HPP
#include "pow.hpp"
#include "ceil.hpp"
#include "floor.hpp"
namespace t_math
{
   inline long double round(double x, int precision)
   {
      if (floor(x * pow_int(10, precision + 1)) - floor(x * pow_int(10, precision)) * 10 >= 5)
      {
         return (ceil(x * pow_int(10, precision)) * 10) / pow_int(10, precision + 1);
      }
      else if (floor(x * pow_int(10, precision + 1)) - floor(x * pow_int(10, precision)) * 10 < 5)
      {
         return (floor(x * pow_int(10, precision)) * 10) / pow_int(10, precision + 1);
      };
      return x;
   };
}
#endif // ROUND_HPP
