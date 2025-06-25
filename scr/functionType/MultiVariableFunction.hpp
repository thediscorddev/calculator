#pragma once
#include "AbstractFunction.hpp"
#include <vector>
class MultiVariableFunction: public AbstractFunction
{
    protected:
        int ArgCount = 2; //default size
        std::vector<std::shared_ptr<Function_Composed>> Arg;
    public:
        MultiVariableFunction();
        void setArg(std::shared_ptr<Function_Composed> arg);
        void setArg(std::vector<std::shared_ptr<Function_Composed>> arg);
}