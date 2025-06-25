#pragma once
#include "Function.hpp"
#include "Function_Composed.hpp"
#include "Function_Number.hpp"
#include "Function_Operation.hpp"
#include "Function_Variable.hpp"
#include <memory>

class AntiDerivative
{
    private:
    static std::map<std::string, std::function<std::shared_ptr<Function_Composed>(std::shared_ptr<Function_Composed>)>> antiderivativeTable; 
    public:
        static std::shared_ptr<Function_Composed> antiDerivative(std::shared_ptr<Function> Func, int level = 0, bool display = true);
        static std::shared_ptr<Function_Composed> ReverseChainRule(std::shared_ptr<Function> Func, int level = 0, bool display = true);
        static std::shared_ptr<Function_Composed> IntegrationByParts(std::shared_ptr<Function> Func, int level = 0, bool display = true);
        static std::shared_ptr<Function_Composed> QuotientRule(std::shared_ptr<Function> Func, int level = 0, bool display = true);
        static void prepareAntiDerivativeTable();
}