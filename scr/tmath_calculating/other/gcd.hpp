#ifndef GCD_HPP
#define GCD_HPP
namespace t_math
{
    inline int gcd(int first, int second)
    {
        int temp_a = first;
        int temp_b = second;
        while(temp_b != 0)
        {
           int temp = temp_b;
           temp_b = temp_a % temp_b;
           temp_a = temp;  
        }
        return temp_a;
    }
}
#endif