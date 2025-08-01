#include "../scr/Derivative.hpp"
#include "../scr/StepLogger.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
std::map<std::string, std::function<std::shared_ptr<Function_Composed>(std::shared_ptr<Function_Composed>)>> derivative::derivativeTable;
std::shared_ptr<Function_Composed> derivative::Derivative(std::shared_ptr<Function> Func_, int level, bool display)
{
    std::shared_ptr<Function_Composed> finalFunction = std::make_shared<Function_Composed>();
    auto Func = std::dynamic_pointer_cast<Function_Composed>(Func_);
    if (!Func)
    {
        if (std::dynamic_pointer_cast<Function_Variable>(Func_) != nullptr)
        {
            // an variable
            StepLogger::Append("Finding the derivative of ", "Tìm đạo hàm của ", "x", level, display);
            StepLogger::Append("Derivative of x is ", "Đạo hàm của x là ", "1", level, display);
            std::shared_ptr<Function_Number> one = std::make_shared<Function_Number>();
            one->PushOperation("1");
            finalFunction->PushComposed(one);
            return finalFunction;
        }
        StepLogger::Append("Finding the derivative of ", "Tìm đạo hàm của ", Func_->GetData(), level, display);
        StepLogger::Append("For a constant, the derivative is ", "Đối với 1 hằng số, đạo hàm của nó là ", "0", level, display);
        std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
        zero->PushOperation("0");
        finalFunction->PushComposed(zero);
        return finalFunction;
    }
    StepLogger::Append("Finding the derivative of ", "Tìm đạo hàm của ", Func->toLatexString(), level, display);
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
                    finalFunction->PushComposed(ChainRule(Func, level + 1, display));
                }
                else
                {
                    // StepLogger::Append("Finding the derivative of x", "Tìm đạo hàm của x", "", level);
                    StepLogger::Append("Derivative of x is ", "Đạo hàm của x là ", " 1", level, display);
                    std::shared_ptr<Function_Number> one = std::make_shared<Function_Number>();
                    one->PushOperation("1");
                    finalFunction->PushComposed(one);
                }
            }
            else
            {
                // StepLogger::Append("Finding the derivative of a constant", "Tìm đạo hàm của hằng số", "", level);
                StepLogger::Append("Derivative of a constant is ", "Đạo hàm của 1 hằng số là ", "0", level, display);
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
                finalFunction->PushComposed(ChainRule(Func->GetComposedData().at(0), level + 1, display));
            else
                finalFunction->PushComposed(ChainRule(Func, level + 1, display));
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
                        finalFunction->PushComposed(Derivative(Arg, level + 1, display));
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
                    finalFunction->PushComposed(Derivative(Arg, level + 1, display));
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
                            finalFunction->PushComposed(ProductRule(Arg, level + 1, display));
                            // chain rule
                        }
                        else if (ptr->GetData() == "/")
                        {
                            finalFunction->PushComposed(QuotientRule(Arg, level + 1, display));
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
            finalFunction->PushComposed(ChainRule(Func, level + 1, display));
        }
    }
    return finalFunction;
}

std::shared_ptr<Function_Composed> derivative::ChainRule(std::shared_ptr<Function> Func_, int level, bool display)
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
    StepLogger::Append("Applying Chain rule for ", "Áp dụng quy tắc chuỗi cho hàm ", Func->toLatexString(), level, display);
    auto Arg = std::make_shared<Function_Composed>();
    for (auto &a : Func->GetComposedData())
    {
        Arg->PushComposed(a);
    }
    StepLogger::Append("Chain rule is: ", "Quy tắc chuỗi có công thức sau: ", "\\frac{d}{dx}f(g(x)) = f'(g(x)) \\cdot g(x)", level, display);
    StepLogger::Append("With g(x) = ", "với g(x) = ", Arg->toLatexString(), level, display);
    if (Func->GetData() != "ComposedOperationSpecialNoInitalized")
    {
        std::shared_ptr<Function_Operation> multiple = std::make_shared<Function_Operation>();
        StepLogger::Append("With f(x) = ", "với f(x) = ", Func->GetData() + "x)", level, display);
        FinalFunction->PushComposed(derivativeTable[Func->GetData()](Func));
        multiple->PushOperation("*");
        FinalFunction->PushComposed(multiple);
    }
    FinalFunction->PushComposed(Derivative(Arg, level + 1, display));
    StepLogger::Append("After applying chain rule, the derivative is: ", "Sau khi áp dụng quy tắc chuỗi, đạo hàm của nó là: ", FinalFunction->toLatexString(), level, display);
    return FinalFunction;
}
std::shared_ptr<Function_Composed> derivative::ProductRule(std::shared_ptr<Function> Func_, int level, bool display)
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
    StepLogger::Append("Applying Product rule for ", "Áp dụng quy tắc tích cho hàm ", Func->toLatexString(), level, display);
    auto fx = Func->GetComposedData().at(0);
    auto gx = std::make_shared<Function_Composed>();
    for (int i = 2; i < Func->GetComposedData().size(); i++)
    {
        gx->PushComposed(Func->GetComposedData().at(i));
    }
    StepLogger::Append("Product rule is: ", "Quy tắc tích có công thưc sau: ", "\\frac{d}{dx}(f(x)\\cdot g(x)) = f'(x)g(x) + f(x)g'(x)", level, display);
    auto ptr = std::dynamic_pointer_cast<Function_Composed>(fx);
    if (ptr)
    {
        StepLogger::Append("With f(x) = ", "Với f(x) = ", ptr->toLatexString(), level, display);
    }
    else
    {
        StepLogger::Append("With f(x) =", "Với f(x) = ", fx->GetData(), level, display);
    }
    StepLogger::Append("With g(x) =", "Với g(x) = ", gx->toLatexString(), level);
    FinalFunction->PushComposed(Derivative(fx, level + 1, display));
    std::shared_ptr<Function_Operation> multiple = std::make_shared<Function_Operation>();
    multiple->PushOperation("*");
    FinalFunction->PushComposed(multiple);
    FinalFunction->PushComposed(gx);
    std::shared_ptr<Function_Operation> addition = std::make_shared<Function_Operation>();
    addition->PushOperation("+");
    FinalFunction->PushComposed(addition);
    FinalFunction->PushComposed(Derivative(gx, level + 1, display));
    std::shared_ptr<Function_Operation> multiple1 = std::make_shared<Function_Operation>();
    multiple1->PushOperation("*");
    FinalFunction->PushComposed(multiple1);
    FinalFunction->PushComposed(fx);
    StepLogger::Append("After product rule, the derivative is: ", "Sau quy tắc tích, đạo hàm của nó là: ", FinalFunction->toLatexString(), level, display);
    return FinalFunction;
}
std::shared_ptr<Function_Composed> derivative::QuotientRule(std::shared_ptr<Function> Func_, int level, bool display)
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
    StepLogger::Append("Applying Quotient rule for ", "Áp dụng quy tắc thương cho hàm ", Func->toLatexString(), level, display);
    StepLogger::Append("Quotient rule is: ", "Quy tắc thương có công thưc sau: ", "\\frac{d}{dx}\\frac{f(x)}{g(x)} = \\frac{f'(x)g(x) - f(x)g'(x)}{g(x)^2}", level, display);
    auto gx = Func->GetComposedData().at(2);
    auto fx = std::make_shared<Function_Composed>();
    fx->PushComposed(Func->GetComposedData().at(0));
    for (int i = 3; i < Func->GetComposedData().size(); i++)
    {
        fx->PushComposed(Func->GetComposedData().at(i));
    }
    auto ptr = std::dynamic_pointer_cast<Function_Composed>(gx);
    StepLogger::Append("With f(x) = ", "Với f(x) = ", fx->toLatexString(), level, display);
    if (ptr)
    {
        StepLogger::Append("With g(x) = ", "Với g(x) = ", ptr->toLatexString(), level, display);
    }
    else
    {
        StepLogger::Append("With g(x) = ", "Với g(x) = ", gx->GetData(), level, display);
    }
    std::shared_ptr<Function_Composed> FinalFunctionUp = std::make_shared<Function_Composed>();
    // term1 = f'(x) * g(x)
    auto term1 = std::make_shared<Function_Composed>();
    term1->PushComposed(Derivative(fx, level + 1, display));
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
    term2->PushComposed(Derivative(gx, level + 1, display));
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
    StepLogger::Append("After quotient rule: ", "Sau quy tắc thương, đạo hàm của nó là: ", FinalFunction->toLatexString(), level, display);
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
    derivativeTable["squared("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        Multiple->PushOperation("*");
        number->PushOperation("2");
        finalFunc->PushComposed(number);
        finalFunc->PushComposed(Multiple);
        finalFunc->PushComposed(func->GetComposedData());
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
    derivativeTable["erf("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        // e^(-x^2)
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        tempFunc1->PushOperation("exp(");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        Multiple->PushOperation("*");
        number->PushOperation("-1");
        tempFunc1->PushComposed(number);
        tempFunc1->PushComposed(Multiple);
        tempFunc1->PushComposed(tempFunc2);
        // 2/sqrt(pi)
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        number2->PushOperation("1.128379167");
        std::shared_ptr<Function_Operation> Multiple2 = std::make_shared<Function_Operation>();
        Multiple2->PushOperation("*");
        // Put it all
        finalFunc->PushComposed(number2);
        finalFunc->PushComposed(Multiple2);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["erfc("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        // e^(-x^2)
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Operation> Multiple = std::make_shared<Function_Operation>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        tempFunc1->PushOperation("exp(");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        Multiple->PushOperation("*");
        number->PushOperation("-1");
        tempFunc1->PushComposed(number);
        tempFunc1->PushComposed(Multiple);
        tempFunc1->PushComposed(tempFunc2);
        // 2/sqrt(pi)
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        number2->PushOperation("1.128379167");
        std::shared_ptr<Function_Operation> Multiple2 = std::make_shared<Function_Operation>();
        Multiple2->PushOperation("*");
        // Put it all
        finalFunc->PushComposed(number2);
        finalFunc->PushComposed(Multiple2);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["erfi("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        // e^(-x^2)
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        tempFunc1->PushOperation("exp(");
        tempFunc2->PushOperation("squared(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(tempFunc2);
        // 2/sqrt(pi)
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        number2->PushOperation("1.128379167");
        std::shared_ptr<Function_Operation> Multiple2 = std::make_shared<Function_Operation>();
        Multiple2->PushOperation("*");
        // Put it all
        finalFunc->PushComposed(number2);
        finalFunc->PushComposed(Multiple2);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["productlog("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc3 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        number->PushOperation("1");
        std::shared_ptr<Function_Operation> multiply = std::make_shared<Function_Operation>();
        multiply->PushOperation("*");
        std::shared_ptr<Function_Operation> addition = std::make_shared<Function_Operation>();
        addition->PushOperation("+");
        tempFunc2->PushOperation("productlog(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc3->PushComposed(number);
        tempFunc3->PushComposed(addition);
        tempFunc3->PushComposed(tempFunc2);
        tempFunc1->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(multiply);
        tempFunc1->PushComposed(tempFunc3);
        // 2/sqrt(pi)
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        number2->PushOperation("1");
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        division->PushOperation("/");
        // Put it all
        finalFunc->PushComposed(number2);
        finalFunc->PushComposed(division);
        finalFunc->PushComposed(tempFunc1);
        return finalFunc;
    };
    derivativeTable["plogalter("] = [](std::shared_ptr<Function_Composed> func)
    {
        std::shared_ptr<Function_Composed> finalFunc = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc1 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc2 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Composed> tempFunc3 = std::make_shared<Function_Composed>();
        std::shared_ptr<Function_Number> number = std::make_shared<Function_Number>();
        number->PushOperation("1");
        std::shared_ptr<Function_Operation> multiply = std::make_shared<Function_Operation>();
        multiply->PushOperation("*");
        std::shared_ptr<Function_Operation> addition = std::make_shared<Function_Operation>();
        addition->PushOperation("+");
        tempFunc2->PushOperation("plogalter(");
        tempFunc2->PushComposed(func->GetComposedData());
        tempFunc3->PushComposed(number);
        tempFunc3->PushComposed(addition);
        tempFunc3->PushComposed(tempFunc2);
        tempFunc1->PushComposed(func->GetComposedData());
        tempFunc1->PushComposed(multiply);
        tempFunc1->PushComposed(tempFunc3);
        // 2/sqrt(pi)
        std::shared_ptr<Function_Number> number2 = std::make_shared<Function_Number>();
        number2->PushOperation("1");
        std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
        division->PushOperation("/");
        // Put it all
        finalFunc->PushComposed(number2);
        finalFunc->PushComposed(division);
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