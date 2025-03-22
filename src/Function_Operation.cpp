#include "../scr/Function_Operation.hpp"
Function_Operation::Function_Operation()
{
    Type = "Operation";
}
void Function_Operation::PushOperation(std::string& Operation)
{
    OperationType = Operation;
}
std::string & Function_Operation::GetData()
{
    return OperationType;
}