#include "../../scr/functionType/MultiVariableFunction.hpp"
#include <stdexcept>
MultiVariableFunction::MultiVariableFunction() : AbstractFunction()
{
    argType = 2;
}
void MultiVariableFunction::setArg(std::shared_ptr<Function_Composed> arg)
{
    if(ArgCount != 1) throw std::logic_error("Arg count mismatch");
    Arg.push_back(arg);
}
void MultiVariableFunction::setArg(std::vector<std::shared_ptr<Function_Composed>> arg)
{
    if (arg.size() > 0)
    {
        if(arg.size() != ArgCount) throw std::logic_error("Arg count mismatch");
        for(auto & el: arg)
        {
            Arg.push_back(el);
        }
    }
}