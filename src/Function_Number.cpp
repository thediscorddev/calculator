#include "../scr/Function_Number.hpp"
Function_Number::Function_Number()
{
    Type = "Number";
}
void Function_Number::PushOperation(std::string& Operation)
{
    Number = Operation; //This do includes constant like X, x, y, pi, e,...
}
std::string & Function_Number::GetData()
{
    return Number;
}