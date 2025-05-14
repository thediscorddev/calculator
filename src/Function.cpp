#include "../scr/Function.hpp"
Function::Function()
{
    Type = "baseClass";
}
std::string Function::GetFunctionType()
{
    return Type;
}
std::string Function::Getlabel()
{
    return Label;
}
void Function::SetLabel(const std::string& label) {
    Label = label;
}