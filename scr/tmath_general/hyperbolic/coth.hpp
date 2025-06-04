#ifndef COTH_HPP
#define COTH_HPP
#include "tanh.hpp"
namespace t_math 
{
		inline double coth(double args) 
		{
				return 1/tanh(args);
		};
};
#endif // COTH_HPP