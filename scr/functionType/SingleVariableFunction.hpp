#pragma once
#include "AbstractFunction.hpp"
class SingleVariableFunction: public AbstractFunction
{
    protected:
        std::shared_ptr<Function_Composed> Arg;
    public:
        SingleVariableFunction();
        void setArg(std::shared_ptr<Function_Composed> arg);
        void setArg(std::vector<std::shared_ptr<Function_Composed>> arg);
}