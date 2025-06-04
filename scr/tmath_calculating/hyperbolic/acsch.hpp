#ifndef ACSCH_HPP
#define ACSCH_HPP
#include "../general/ln.hpp"
#include "../general/sqrt.hpp"
#include "../general/abs.hpp"
#include <stdexcept>
namespace t_math 
{
	inline double acsch(double args) 
	{
		if(args == 0)
			throw std::out_of_range("acsch only accepts value that is not 0.");
		return ln(1/args + sqrt(1/(args*args) + 1));
	};
};
#endif // ACSCH_HPP