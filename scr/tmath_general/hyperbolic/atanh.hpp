#ifndef ATANH_HPP
#define ATANH_HPP
#include "../general/ln.hpp"
#include "../general/abs.hpp"
#include <stdexcept>
namespace t_math 
{
	inline double atanh(double args) 
	{
		if(abs(args) > 1)
			throw std::out_of_range("atanh only accepts value that is within -1 and 1 but not -1 and 1 itself.");
		return 0.5 * ln((1+args)/(1-args));
	};
};
#endif // ATANH_HPP