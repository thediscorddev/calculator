#ifndef ASINH_HPP
#define ASINH_HPP
#include "../general/ln.hpp"
#include "../general/sqrt.hpp"
namespace t_math 
{
	inline double asinh(double args) 
	{
		return ln(args + sqrt(args*args+1));
	};
};
#endif // ASINH_HPP