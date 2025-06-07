#pragma once
#include "Function.hpp"
#include "Function_Composed.hpp"
#include "Function_Number.hpp"
#include "Function_Operation.hpp"
#include "Function_Variable.hpp"
#include <memory>
class AntiDerivativeExpression: public Function_Composed
{
    private:
        std::shared_ptr<Function_Composed> OriginalExpression;
        std::shared_ptr<Function_Composed> AntiderivativeOfFunc;
        bool IsFinish = false;
    public:
        AntiDerivativeExpression();
};