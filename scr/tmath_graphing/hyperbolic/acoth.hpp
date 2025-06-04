#ifndef ACOTH_HPP
#define ACOTH_HPP
#include "../general/ln.hpp"
#include "../general/abs.hpp"
#include <stdexcept>
namespace t_math 
{
	inline double acoth(double args) 
	{
		if(abs(args) < 1)
			throw std::out_of_range("acoth only accepts value that is not inside the range of -1 and 1.");
		return 0.5 * ln((args+1)/(args-1));
	};
};
#endif // ACOTH_HPP