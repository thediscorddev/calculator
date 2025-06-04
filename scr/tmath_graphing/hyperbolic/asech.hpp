#ifndef ASECH_HPP
#define ASECH_HPP
#include "../general/ln.hpp"
#include "../general/sqrt.hpp"
#include "../general/abs.hpp"
#include <stdexcept>
namespace t_math 
{
	inline double asech(double args) 
	{
		if(args <= 0 || args > 1)
			throw std::out_of_range("asech only accepts value that is inside the range of 0 and 1 but not 0 itself.");
		return ln(1/args + sqrt(1/(args*args) - 1));
	};
};
#endif // ASECH_HPP