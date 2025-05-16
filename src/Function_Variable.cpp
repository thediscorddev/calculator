#include "../scr/Function_Variable.hpp"
Function_Variable::Function_Variable()
{
    Type = "variable";
}
void Function_Variable::PushOperation(const std::string& Operation)
{
    Number = Operation; //This do includes constant like X, x, y, pi, e,...
}
std::string & Function_Variable::GetData()
{
    return Number;
}