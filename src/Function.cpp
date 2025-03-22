#include "../scr/Function.hpp"
Function::Function()
{
    Type = "baseClass";
}
std::string Function::GetFunctionType()
{
    return Type;
}