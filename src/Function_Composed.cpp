#include "../scr/Function_Composed.hpp"
Function_Composed::Function_Composed()
{
    Type = "Composed";
    OutlineFunc = "ComposedOperationSpecialNoInitalized";
}
void Function_Composed::PushOperation(std::string& Operation)
{
    OutlineFunc = Operation;
}
void Function_Composed::PushComposed(std::shared_ptr<Function> Composed)
{
    ComposedList.push_back(Composed);
}
std::string & Function_Composed::GetData()
{
    return OutlineFunc;
}
std::vector<std::shared_ptr<Function>> & Function_Composed::GetComposedData()
{
    return ComposedList;
}