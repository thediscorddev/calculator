#include "../../scr/functionType/SingleVariableFunction.hpp"
#include <stdexcept>
SingleVariableFunction::SingleVariableFunction() : AbstractFunction()
{
    argType = 1;
}
void SingleVariableFunction::setArg(std::shared_ptr<Function_Composed> arg)
{
    Arg = arg;
}
void SingleVariableFunction::setArg(std::vector<std::shared_ptr<Function_Composed>> arg)
{
    if (arg.size() > 0)
    {
        Arg = arg.at(0);
    }
}