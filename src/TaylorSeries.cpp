#include "../scr/TaylorSeries.hpp"
#include <TMATH/t_math.hpp>
std::shared_ptr<Function_Number> TaylorSeries::N_DerivativeAt(std::shared_ptr<Function_Composed> function, double index, int NumOfDerivative)
{
    std::shared_ptr<Function_Number> num = std::make_shared<Function_Number>();
    num->PushOperation(N_Derivative(function, NumOfDerivative)->Calculate(index).GetData());
    return num;
}
std::shared_ptr<Function_Composed> TaylorSeries::N_Derivative(std::shared_ptr<Function_Composed> function, int NumOfDerivative)
{
    if (NumOfDerivative <= 0)
    {
        return function;
    }
    else
    {
        return N_Derivative(derivative::Derivative(function, 0, false), NumOfDerivative - 1);
    }
}

std::shared_ptr<Function_Composed> TaylorSeries::GenerateTaylorSeries(std::shared_ptr<Function_Composed> function, double center, int terms)
{
    std::shared_ptr<Function_Composed> func = std::make_shared<Function_Composed>();
    for (int i = 0; i < terms; i++)
    {
        if (i > 0)
        {
            std::shared_ptr<Function_Operation> Addition = std::make_shared<Function_Operation>();
            Addition->PushOperation("+");
            func->PushComposed(Addition);
        }
        std::shared_ptr<Function_Number> term = N_DerivativeAt(function, center, i);
        func->PushComposed(term);
        std::shared_ptr<Function_Operation> Divis = std::make_shared<Function_Operation>();
        Divis->PushOperation("/");
        int factorial = t_math::fac(i);
        func->PushComposed(Divis);
        std::shared_ptr<Function_Number> num_ = std::make_shared<Function_Number>();
        num_->PushOperation(std::to_string(factorial));
        func->PushComposed(num_);
        for (int j = 0; j < i; j++)
        {
            std::shared_ptr<Function_Composed> Xterm = std::make_shared<Function_Composed>();
            std::shared_ptr<Function_Variable> variable = std::make_shared<Function_Variable>();
            variable->PushOperation("x");
            std::shared_ptr<Function_Operation> Minus = std::make_shared<Function_Operation>();
            Minus->PushOperation("-");
            std::shared_ptr<Function_Number> num = std::make_shared<Function_Number>();
            num->PushOperation(std::to_string(center));
            Xterm->PushComposed(variable);
            Xterm->PushComposed(Minus);
            Xterm->PushComposed(num);
            std::shared_ptr<Function_Operation> Mul1 = std::make_shared<Function_Operation>();
            Mul1->PushOperation("*");
            func->PushComposed(Mul1);
            func->PushComposed(Xterm);
        }
    }
    return func;
}
std::shared_ptr<Function_Composed> TaylorSeries::GenerateMaclaurinSeries(std::shared_ptr<Function_Composed> function, int terms)
{
    return GenerateTaylorSeries(function, 0, terms);
}