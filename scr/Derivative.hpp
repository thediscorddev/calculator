#pragma once
#include "Function.hpp"
#include "Function_Composed.hpp"
#include "Function_Number.hpp"
#include "Function_Operation.hpp"
#include "Function_Variable.hpp"
#include <memory>

class derivative
{
    private:
        static std::map<std::string, std::function<std::shared_ptr<Function_Composed>(std::shared_ptr<Function_Composed>)>> derivativeTable; 
    public:
        static std::shared_ptr<Function_Composed> Derivative(std::shared_ptr<Function> Func);
        static std::shared_ptr<Function_Composed> ChainRule(std::shared_ptr<Function> Func);
        static std::shared_ptr<Function_Composed> ProductRule(std::shared_ptr<Function> Func);
        static std::shared_ptr<Function_Composed> QuotientRule(std::shared_ptr<Function> Func);
        static void prepareDerivativeTable();
};