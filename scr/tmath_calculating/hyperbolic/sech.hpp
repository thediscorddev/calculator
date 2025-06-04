#ifndef SECH_HPP
#define SECH_HPP
#include "cosh.hpp"
namespace t_math 
{
		inline double sech(double args) 
		{
				return 1/cosh(args);
		};
};
#endif // SECH_HPP