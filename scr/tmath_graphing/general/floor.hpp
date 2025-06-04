#ifndef FLOOR_HPP
#define FLOOR_HPP
namespace t_math
{
    inline long floor(double x)
    {
        int int_part = static_cast<int>(x); // Get the integer part of x
        if (x > int_part)
        {
            return int_part; // If x is greater than its integer part, return
        }
        else
        {
            return int_part; // Otherwise, x is already an integer, so return it
        }
    }
}
#endif // FLOOR_HPP
