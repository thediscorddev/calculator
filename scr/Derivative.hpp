#pragma once
#include "Function.hpp"
#include "Function_Composed.hpp"
#include "Function_Number.hpp"
#include "Function_Operation.hpp"
#include <memory>
class Derivative
{
    public:
        static std::shared_ptr<Function_Composed> Derivative(std::shared_ptr<Function_Composed> Func);
        static std::shared_ptr<Function_Composed> ChainRule(std::shared_ptr<Function_Composed> Func);
        static std::shared_ptr<Function_Composed> ProductRule(std::shared_ptr<Function_Composed> Func);
        static std::shared_ptr<Function_Composed> QuotientRule(std::shared_ptr<Function_Composed> Func);
        static void prepareDerivativeTable();
};