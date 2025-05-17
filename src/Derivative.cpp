#include "../scr/Derivative.hpp"
#include "../scr/StepLogger.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
std::map<std::string, std::function<std::shared_ptr<Function_Composed>(std::shared_ptr<Function_Composed>)>> derivative::derivativeTable;
std::shared_ptr<Function_Composed> derivative::Derivative(std::shared_ptr<Function> Func_, int level)
{
    std::shared_ptr<Function_Composed> finalFunction = std::make_shared<Function_Composed>();
    auto Func = std::dynamic_pointer_cast<Function_Composed>(Func_);
    if (!Func)
    {
        if (std::dynamic_pointer_cast<Function_Variable>(Func_) != nullptr)
        {
            // an variable
            StepLogger::Append("Finding the derivative of ", "x", level);
            StepLogger::Append("Derivative of x is ", "1", level);
            std::shared_ptr<Function_Number> one = std::make_shared<Function_Number>();
            one->PushOperation("1");
            finalFunction->PushComposed(one);
            return finalFunction;
        }
        StepLogger::Append("Finding the derivative of ", Func->GetData(), level);
        StepLogger::Append("For a constant, the derivative is 0", "", level);
        std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
        zero->PushOperation("0");
        finalFunction->PushComposed(zero);
        return finalFunction;
    }
    StepLogger::Append("Finding the derivative of ", Func->toLatexString(), level);
    if (Func->GetComposedData().size() == 0)
    {
        std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
        zero->PushOperation("0");
        finalFunction->PushComposed(zero);
    }
    else if (Func->GetComposedData().size() == 1)
    {
        auto ptr = std::dynamic_pointer_cast<Function_Composed>(Func->GetComposedData().at(0));
        if (!ptr)
        {
            if (std::dynamic_pointer_cast<Function_Variable>(Func->GetComposedData().at(0)) != nullptr)
            {
                // an variable
                if (Func->GetData() != "ComposedOperationSpecialNoInitalized")
                {
                    finalFunction->PushComposed(ChainRule(Func, level + 1));
                }
                else
                {
                    StepLogger::Append("Finding the derivative of x", "", level);
                    StepLogger::Append("Derivative of x is", " 1", level);
                    std::shared_ptr<Function_Number> one = std::make_shared<Function_Number>();
                    one->PushOperation("1");
                    finalFunction->PushComposed(one);
                }
            }
            else
            {
                StepLogger::Append("Finding the derivative of ", "", level);
                StepLogger::Append("Derivative of x is", "1", level);
                std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
                zero->PushOperation("0");
                finalFunction->PushComposed(zero);
            }
            // Not a composed, a number or an operation
        }
        else
        {
            // the pointer exist
            // Since we only have 1 arg
            if (Func->GetData() == "ComposedOperationSpecialNoInitalized")
                finalFunction->PushComposed(ChainRule(Func->GetComposedData().at(0),level+1));
            else
                finalFunction->PushComposed(ChainRule(Func,level+1));
        }
    }
    else
    {
        // Has more term
        bool hasAddOrSubStract = false;
        std::string sign = "";
        std::shared_ptr<Function_Composed> Arg = std::make_shared<Function_Composed>();
        if (Func->GetData() == "ComposedOperationSpecialNoInitalized")
        {
            for (auto &a : Func->GetComposedData())
            {
                if (!a)
                    continue;
                auto ptr = std::dynamic_pointer_cast<Function_Operation>(a);
                if (ptr)
                {
                    if (ptr->GetData() == "+" || ptr->GetData() == "-")
                    {
                        if (sign != "")
                        {
                            std::shared_ptr<Function_Operation> sign_ = std::make_shared<Function_Operation>();
                            sign_->PushOperation(sign);
                            finalFunction->PushComposed(sign_);
                        }
                        finalFunction->PushComposed(Derivative(Arg, level + 1));
                        hasAddOrSubStract = true;
                        sign = ptr->GetData();
                        // clean the arg
                        Arg = std::make_shared<Function_Composed>();
                    }
                    else
                        Arg->PushComposed(a);
                }
                else
                    Arg->PushComposed(a);
            }
            if (hasAddOrSubStract)
            {
                if (Arg->GetComposedData().size() > 0)
                {
                    if (sign != "")
                    {
                        std::shared_ptr<Function_Operation> sign_ = std::make_shared<Function_Operation>();
                        sign_->PushOperation(sign);
                        finalFunction->PushComposed(sign_);
                    }
                    finalFunction->PushComposed(Derivative(Arg, level + 1));
                    hasAddOrSubStract = false;
                    // clean the arg
                    Arg = std::make_shared<Function_Composed>();
                }
            }
            else
            {
                // What we did is just a bunch of * and / operation
                // We should move around
                // once we move around
                if (Arg->GetComposedData().size() >= 3)
                {
                    auto ptr = std::dynamic_pointer_cast<Function_Operation>(Arg->GetComposedData().at(1));
                    if (ptr)
                    {
                        if (ptr->GetData() == "*")
                        {
                            finalFunction->PushComposed(ProductRule(Arg,level+1));
                            // chain rule
                        }
                        else if (ptr->GetData() == "/")
                        {
                            finalFunction->PushComposed(QuotientRule(Arg,level+1));
                            // quotient rule
                        }
                    }
                    else
                        throw std::runtime_error("Syntax error.");
                }
            }
        }
        else
        {
            // We will combine the inner function into 1 BIG function
            for (auto &a : Func->GetComposedData())
            {
                if (!a)
                    continue;
                Arg->PushComposed(a);
            }
            finalFunction->PushComposed(ChainRule(Func,level+1));
        }
    }
    return finalFunction;
}

std::shared_ptr<Function_Composed> derivative::ChainRule(std::shared_ptr<Function> Func_, int level)
{
    std::shared_ptr<Function_Composed> FinalFunction = std::make_shared<Function_Composed>();
    auto Func = std::dynamic_pointer_cast<Function_Composed>(Func_);
    if (!Func)
    {
        if (std::dynamic_pointer_cast<Function_Variable>(Func_) != nullptr)
        {
            // an variable
            std::shared_ptr<Function_Number> one = std::make_shared<Function_Number>();
            one->PushOperation("1");
            FinalFunction->PushComposed(one);
            return FinalFunction;
        }
        std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
        zero->PushOperation("0");
        FinalFunction->PushComposed(zero);
        return FinalFunction;
    }
    StepLogger::Append("Applying Chain rules for ", Func->toLatexString(), level);
    auto Arg = std::make_shared<Function_Composed>();
    for (auto &a : Func->GetComposedData())
    {
        Arg->PushComposed(a);
    }
    StepLogger::Append("Chain rules has the following formula: d/dx (f(g(x))) = f'(g(x)) * g(x)", "", level);
    FinalFunction->PushComposed(Derivative(Arg, level + 1));
    StepLogger::Append("With g(x) is:",Arg->toLatexString(), level);
    if (Func->GetData() != "ComposedOperationSpecialNoInitalized")
    {
        std::shared_ptr<Function_Operation> multiple = std::make_shared<Function_Operation>();
        multiple->PushOperation("*");
        FinalFunction->PushComposed(multiple);
        StepLogger::Append("With f(x) is: "+Func->GetData()+"x)","", level);
        FinalFunction->PushComposed(derivativeTable[Func->GetData()](Func));
    }
    StepLogger::Append("After applying chain rules, the final derivative is: ", FinalFunction->toLatexString(), level);
    return FinalFunction;
}
std::shared_ptr<Function_Composed> derivative::ProductRule(std::shared_ptr<Function> Func_, int level)
{
    // Derivative class always assume that we have more than 3 args
    std::shared_ptr<Function_Composed> FinalFunction = std::make_shared<Function_Composed>();
    auto Func = std::dynamic_pointer_cast<Function_Composed>(Func_);
    if (!Func)
    {
        if (std::dynamic_pointer_cast<Function_Variable>(Func_) != nullptr)
        {
            // an variable
            std::shared_ptr<Function_Number> one = std::make_shared<Function_Number>();
            one->PushOperation("1");
            FinalFunction->PushComposed(one);
            return FinalFunction;
        }
        std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
        zero->PushOperation("0");
        FinalFunction->PushComposed(zero);
        return FinalFunction;
    }
    StepLogger::Append("Applying Product rules for", Func->toLatexString(), level);
    auto fx = Func->GetComposedData().at(0);
    auto gx = std::make_shared<Function_Composed>();
    for (int i = 2; i < Func->GetComposedData().size(); i++)
    {
        gx->PushComposed(Func->GetComposedData().at(i));
    }
    StepLogger::Append("Product rules is: d/dx(f(x)*g(x)) = f'(x)g(x) + f(x)g'(x)", "", level);
    auto ptr = std::dynamic_pointer_cast<Function_Composed>(fx);
    if(ptr)
    {
        StepLogger::Append("With f(x) =", ptr->toLatexString(), level);
    }else
    {
        StepLogger::Append("With f(x) =", fx->GetData(), level);
    }
    StepLogger::Append("With g(x) =", gx->toLatexString(), level);
    FinalFunction->PushComposed(Derivative(fx, level + 1));
    std::shared_ptr<Function_Operation> multiple = std::make_shared<Function_Operation>();
    multiple->PushOperation("*");
    FinalFunction->PushComposed(multiple);
    FinalFunction->PushComposed(gx);
    std::shared_ptr<Function_Operation> addition = std::make_shared<Function_Operation>();
    addition->PushOperation("+");
    FinalFunction->PushComposed(addition);
    FinalFunction->PushComposed(Derivative(gx, level + 1));
    std::shared_ptr<Function_Operation> multiple1 = std::make_shared<Function_Operation>();
    multiple1->PushOperation("*");
    FinalFunction->PushComposed(multiple1);
    FinalFunction->PushComposed(fx);
    StepLogger::Append("After product rule: ", FinalFunction->toLatexString(), level);
    return FinalFunction;
}
std::shared_ptr<Function_Composed> derivative::QuotientRule(std::shared_ptr<Function> Func_, int level)
{
    std::shared_ptr<Function_Composed> FinalFunction = std::make_shared<Function_Composed>();
    auto Func = std::dynamic_pointer_cast<Function_Composed>(Func_);
    if (!Func)
    {
        if (std::dynamic_pointer_cast<Function_Variable>(Func_) != nullptr)
        {
            // an variable
            std::shared_ptr<Function_Number> one = std::make_shared<Function_Number>();
            one->PushOperation("1");
            FinalFunction->PushComposed(one);
            return FinalFunction;
        }
        std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
        zero->PushOperation("0");
        FinalFunction->PushComposed(zero);
        return FinalFunction;
    }
    /*
    f(x) / g(x) * h(x) * c / ...
    0    1  2   3  4   5  6 7  8+

    */
   StepLogger::Append("Applying Quotient rules for", Func->toLatexString(), level);
    StepLogger::Append("Quotient rules is: d/dx(f(x)/g(x)) = (f'(x)g(x) - f(x)g'(x))/(g(x)^2)", "", level);
    auto gx = Func->GetComposedData().at(2);
    auto fx = std::make_shared<Function_Composed>();
    fx->PushComposed(Func->GetComposedData().at(0));
    for (int i = 3; i < Func->GetComposedData().size(); i++)
    {
        fx->PushComposed(Func->GetComposedData().at(i));
    }
    auto ptr = std::dynamic_pointer_cast<Function_Composed>(gx);
    StepLogger::Append("With f(x) =", fx->toLatexString(), level);
    if (ptr)
    {
        StepLogger::Append("With g(x) =", ptr->toLatexString(), level);
    }else {
        StepLogger::Append("With g(x) =", gx->GetData(), level);
    }
    std::shared_ptr<Function_Composed> FinalFunctionUp = std::make_shared<Function_Composed>();
    // term1 = f'(x) * g(x)
    auto term1 = std::make_shared<Function_Composed>();
    term1->PushComposed(Derivative(fx, level + 1));
    auto mul1 = std::make_shared<Function_Operation>();
    mul1->PushOperation("*");
    term1->PushComposed(mul1);
    term1->PushComposed(gx);
    // term2 = f(x) * g'(x)
    auto term2 = std::make_shared<Function_Composed>();
    term2->PushComposed(fx);
    auto mul2 = std::make_shared<Function_Operation>();
    mul2->PushOperation("*");
    term2->PushComposed(mul2);
    term2->PushComposed(Derivative(gx, level + 1));
    // FinalFunctionUp = term1 - term2
    FinalFunctionUp->PushComposed(term1);
    auto minus = std::make_shared<Function_Operation>();
    minus->PushOperation("-");
    FinalFunctionUp->PushComposed(minus);
    FinalFunctionUp->PushComposed(term2);
    std::shared_ptr<Function_Composed> PowDe = std::make_shared<Function_Composed>();
    PowDe->PushOperation("squared(");
    PowDe->PushComposed(gx);
    std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
    division->PushOperation("/");
    FinalFunction->PushComposed(FinalFunctionUp);
    FinalFunction->PushComposed(division);
    FinalFunction->PushComposed(PowDe);
    StepLogger::Append("After quotient rule: ", FinalFunction->toLatexString(), level);
    return FinalFunction;
}
void derivative::prepareDerivativeTable()
{
    derivativeTable["sin("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        finalFunc->PushOperation("cos(");
        finalFunc->PushComposed(func->GetComposedData());
        return finalFunc;
    };
    derivativeTable["cos("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        Multiple->PushOperation("*");
        number->PushOperation("-1");
        tempFunc->PushOperation("sin(");
        tempFunc->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(Multiple);
        finalFunc->PushComposed(tempFunc);
        return finalFunc;
    };
    derivativeTable["tan("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc = std::make_shared<Function_Composed>();
        tempFunc->PushOperation("sec(");
        tempFunc->PushComposed(func->GetComposedData());
        finalFunc->PushOperation("squared(");
        finalFunc->PushComposed(tempFunc);
        return finalFunc;
    };
    derivativeTable["cot("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        Multiple->PushOperation("*");
        number->PushOperation("-1");
        tempFunc2->PushOperation("csc(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("squared(");
        tempFunc1->PushComposed(tempFunc2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(Multiple);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["csc("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> Multiple2 = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        Multiple->PushOperation("*");
        Multiple2->PushOperation("*");
        number->PushOperation("-1");
        tempFunc2->PushOperation("csc(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("cot(");
        tempFunc1->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(Multiple);
        finalFunc->PushComposed(tempFunc1);
        finalFunc->PushComposed(Multiple2);
        finalFunc->PushComposed(tempFunc2);
        return finalFunc;
    };
    derivativeTable["sec("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        Multiple->PushOperation("*");
        tempFunc2->PushOperation("tan(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("sec(");
        tempFunc1->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(tempFunc1);
        finalFunc->PushComposed(Multiple);
        finalFunc->PushComposed(tempFunc2);
        return finalFunc;
    };
    derivativeTable["sinh("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        finalFunc->PushOperation("cosh(");
        finalFunc->PushComposed(func->GetComposedData());
        return finalFunc;
    };
    derivativeTable["cosh("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        finalFunc->PushOperation("sinh(");
        finalFunc->PushComposed(func->GetComposedData());
        return finalFunc;
    };
    derivativeTable["tanh("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc = std::make_shared<Function_Composed>();
        tempFunc->PushOperation("sech(");
        tempFunc->PushComposed(func->GetComposedData());
        finalFunc->PushOperation("squared(");
        finalFunc->PushComposed(tempFunc);
        return finalFunc;
    };
    derivativeTable["coth("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        Multiple->PushOperation("*");
        number->PushOperation("-1");
        tempFunc2->PushOperation("csch(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("squared(");
        tempFunc1->PushComposed(tempFunc2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(Multiple);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["csch("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> Multiple2 = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        Multiple->PushOperation("*");
        Multiple2->PushOperation("*");
        number->PushOperation("-1");
        tempFunc2->PushOperation("csch(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("coth(");
        tempFunc1->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(Multiple);
        finalFunc->PushComposed(tempFunc1);
        finalFunc->PushComposed(Multiple2);
        finalFunc->PushComposed(tempFunc2);
        return finalFunc;
    };
    derivativeTable["sech("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> Multiple2 = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        Multiple->PushOperation("*");
        Multiple2->PushOperation("*");
        number->PushOperation("-1");
        tempFunc2->PushOperation("sech(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("tanh(");
        tempFunc1->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(Multiple);
        finalFunc->PushComposed(tempFunc1);
        finalFunc->PushComposed(Multiple2);
        finalFunc->PushComposed(tempFunc2);
        return finalFunc;
    };
    derivativeTable["arcsin("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> minus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        minus->PushOperation("-");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("sqrt(");
        tempFunc1->PushComposed(number2);
        tempFunc1->PushComposed(minus);
        tempFunc1->PushComposed(tempFunc2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["arccos("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> minus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        minus->PushOperation("-");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("sqrt(");
        tempFunc1->PushComposed(number2);
        tempFunc1->PushComposed(minus);
        tempFunc1->PushComposed(tempFunc2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["arctan("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> plus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        plus->PushOperation("+");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(number2);
        tempFunc1->PushComposed(plus);
        tempFunc1->PushComposed(tempFunc2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["arccot("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> plus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        plus->PushOperation("+");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(number2);
        tempFunc1->PushComposed(plus);
        tempFunc1->PushComposed(tempFunc2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["arcsec("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc3 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc4 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> multiply = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> minus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        minus->PushOperation("-");
        multiply->PushOperation("*");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("sqrt(");
        tempFunc3->PushOperation("abs(");
        tempFunc3->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(tempFunc2);
        tempFunc1->PushComposed(minus);
        tempFunc1->PushComposed(number2);
        tempFunc4->PushComposed(tempFunc3);
        tempFunc4->PushComposed(multiply);
        tempFunc4->PushComposed(tempFunc1);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc4);
        return finalFunc;
    };
    derivativeTable["arccsc("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc3 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc4 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> multiply = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> minus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        minus->PushOperation("-");
        multiply->PushOperation("*");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("sqrt(");
        tempFunc3->PushOperation("abs(");
        tempFunc3->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(tempFunc2);
        tempFunc1->PushComposed(minus);
        tempFunc1->PushComposed(number2);
        tempFunc4->PushComposed(tempFunc3);
        tempFunc4->PushComposed(multiply);
        tempFunc4->PushComposed(tempFunc1);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc4);
        return finalFunc;
    };
    derivativeTable["arcsinh("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> plus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        plus->PushOperation("+");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("sqrt(");
        tempFunc1->PushComposed(number2);
        tempFunc1->PushComposed(plus);
        tempFunc1->PushComposed(tempFunc2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["arccosh("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> minus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        minus->PushOperation("-");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("sqrt(");
        tempFunc1->PushComposed(tempFunc2);
        tempFunc1->PushComposed(minus);
        tempFunc1->PushComposed(number2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["arctanh("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> minus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        minus->PushOperation("-");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(number2);
        tempFunc1->PushComposed(minus);
        tempFunc1->PushComposed(tempFunc2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["arccoth("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> minus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        minus->PushOperation("-");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(number2);
        tempFunc1->PushComposed(minus);
        tempFunc1->PushComposed(tempFunc2);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["arcsech("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc3 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc4 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> multiply = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> minus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        minus->PushOperation("-");
        multiply->PushOperation("*");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("sqrt(");
        tempFunc3->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(number2);
        tempFunc1->PushComposed(minus);
        tempFunc1->PushComposed(tempFunc2);
        tempFunc4->PushComposed(tempFunc3);
        tempFunc4->PushComposed(multiply);
        tempFunc4->PushComposed(tempFunc1);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc4);
        return finalFunc;
    };
    derivativeTable["arccsch("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc3 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc4 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> multiply = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> plus = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        division->PushOperation("/");
        plus->PushOperation("-");
        multiply->PushOperation("*");
        number->PushOperation("1");
        number2->PushOperation("1");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushOperation("sqrt(");
        tempFunc3->PushOperation("abs(");
        tempFunc3->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(tempFunc2);
        tempFunc1->PushComposed(plus);
        tempFunc1->PushComposed(number2);
        tempFunc4->PushComposed(tempFunc3);
        tempFunc4->PushComposed(multiply);
        tempFunc4->PushComposed(tempFunc1);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc4);
        return finalFunc;
    };
    derivativeTable["si("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        division->PushOperation("/");
        tempFunc1->PushOperation("sin(");
        tempFunc1->PushComposed(func->GetComposedData());
        tempFunc2->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(tempFunc1);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc2);
        return finalFunc;
    };
    derivativeTable["shi("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        division->PushOperation("/");
        tempFunc1->PushOperation("sinh(");
        tempFunc1->PushComposed(func->GetComposedData());
        tempFunc2->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(tempFunc1);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc2);
        return finalFunc;
    };
    derivativeTable["chi("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        division->PushOperation("/");
        tempFunc1->PushOperation("cosh(");
        tempFunc1->PushComposed(func->GetComposedData());
        tempFunc2->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(tempFunc1);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc2);
        return finalFunc;
    };
    derivativeTable["ci("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> multiply = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        number->PushOperation("-1");
        multiply->PushOperation("*");
        division->PushOperation("/");
        tempFunc1->PushOperation("cos(");
        tempFunc1->PushComposed(func->GetComposedData());
        tempFunc2->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(multiply);
        finalFunc->PushComposed(tempFunc1);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc2);
        return finalFunc;
    };
    derivativeTable["exp("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        finalFunc->PushOperation("exp(");
        finalFunc->PushComposed(func->GetComposedData());
        return finalFunc;
    };
    derivativeTable["ln("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Composed> tempFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        number->PushOperation("1");
        division->PushOperation("/");
        tempFunc->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc);
        return finalFunc;
    };
    derivativeTable["li("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Composed> tempFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        number->PushOperation("1");
        division->PushOperation("/");
        tempFunc->PushOperation("ln(");
        tempFunc->PushComposed(func->GetComposedData());
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc);
        return finalFunc;
    };
    derivativeTable["sqrt("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Operation> multiply = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Composed> tempFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        number->PushOperation("1");
        number2->PushOperation("2");
        multiply->PushOperation("*");
        division->PushOperation("/");
        tempFunc->PushOperation("sqrt(");
        tempFunc->PushComposed(func->GetComposedData());
        tempFunc2->PushComposed(number2);
        tempFunc2->PushComposed(multiply);
        tempFunc2->PushComposed(tempFunc);
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc2);
        return finalFunc;
    };
}