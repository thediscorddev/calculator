#ifndef SINH_HPP
#define SINH_HPP
#include "../general/pow.hpp"
#include "../general/factorial.hpp"
#include "../t_math_constant.hpp"
#include "../general/abs.hpp"
namespace t_math
{
	inline double sinh(double args) 
	{
		double temp = 0;
		int i = 0;
		if (args < 0) 
			return -1 * sinh(-1 * args);
		if (args == 0) 
			return 0;
		while (abs(pow_int(args,2*i+1) / d_fac(2*i+1)) > t_math_precise) 
		{
			temp+=pow_int(args,2*i+1) / d_fac(2*i+1);
			i++;
		};
		return temp;
	};
};
#endif // SINH_HPP