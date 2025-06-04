#ifndef ABS_HPP
#define ABS_HPP
namespace t_math
{
    template <typename T>
    inline T abs(T args)
    {
        if (args < 0)
            return -1 * args;
        return args;
    };
};
#endif // ABS_H
