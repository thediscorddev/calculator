#ifndef ACOSH_HPP
#define ACOSH_HPP
#include "../general/ln.hpp"
#include "../general/sqrt.hpp"
#include <stdexcept>
namespace t_math 
{
	inline double acosh(double args) 
	{
		if(args < 1)
			throw std::out_of_range("acosh only accepts value that is bigger or equal to 1.");
		return ln(args + sqrt(args*args-1));
	};
};
#endif // ACOSH_HPP