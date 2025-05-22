#include "../scr/Function_Arg_Break.hpp"
Function_Arg_Break::Function_Arg_Break()
{
    Type = "ArgBreak";
    Number = ",";
}
void Function_Arg_Break::PushOperation(const std::string& Operation)
{

}
std::string & Function_Arg_Break::GetData()
{
    return Number;
}