#ifndef CEIL_HPP
#define CEIL_HPP
namespace t_math
{
    inline long ceil(double x)
    {
        int int_part = static_cast<int>(x); // Get the integer part of x
        if (x > int_part)
        {
            return int_part + 1; // If x is greater than its integer part, return the next integer
        }
        else
        {
            return int_part; // Otherwise, x is already an integer, so return it
        }
    }
}
#endif // CEIL_HPP
