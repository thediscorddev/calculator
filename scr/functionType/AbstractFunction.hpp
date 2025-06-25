#pragma once
#include "../Function_Composed.hpp"
#include "../Function_Number.hpp"
#include <memory>
#include <vector>
class AbstractFunction
{
    protected:
        int argType = 0; // 0 = abstract, 1 = single variable, 2 = multi variable
    public:
        void AbstractFunction();
        virtual std::shared_ptr<Function_Number> CalculateNormal() = 0;
        virtual std::shared_ptr<Function_Number> CalculateGraph() = 0;
        virtual std::shared_ptr<Function_Number> CalculatePrecise() = 0;
        int getArgType();
        void setArg(std::shared_ptr<Function_Composed> arg) = 0;
        void setArg(std::vector<std::shared_ptr<Function_Composed>> arg) = 0;
}