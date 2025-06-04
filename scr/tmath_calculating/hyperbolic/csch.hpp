#ifndef CSCH_HPP
#define CSCH_HPP
#include "sinh.hpp"
namespace t_math 
{
		inline double csch(double args) 
		{
				return 1/sinh(args);
		};
};
#endif // CSCH_HPP