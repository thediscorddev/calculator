#ifndef IS_INT
#define IS_INT
namespace t_math
{
    template <typename T>
    inline bool is_int(T arg)
    {
        if (static_cast<int>(arg) - arg == 0)
            return true;
        return false;
    };
}
#endif // IS_INT