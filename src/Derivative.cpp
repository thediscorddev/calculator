#include "../scr/Derivative.hpp"
#include <stdexcept>
#include <algorithm>
std::map<std::string, std::function<std::shared_ptr<Function_Composed>(std::shared_ptr<Function_Composed>)>> derivative::derivativeTable;
std::shared_ptr<Function_Composed> derivative::Derivative(std::shared_ptr<Function> Func_)
{
    std::shared_ptr<Function_Composed> finalFunction = std::make_shared<Function_Composed>();
    auto Func = std::dynamic_pointer_cast<Function_Composed>(Func_);
    if (!Func)
    {
        if (std::dynamic_pointer_cast<Function_Variable>(Func_) != nullptr)
        {
            // an variable
            std::shared_ptr<Function_Number> one = std::make_shared<Function_Number>();
            one->PushOperation("1");
            finalFunction->PushComposed(one);
            return finalFunction;
        }
        std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
        zero->PushOperation("0");
        finalFunction->PushComposed(zero);
        return finalFunction;
    }
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
            // Not a composed, a number or an operation
            std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
            zero->PushOperation("0");
            finalFunction->PushComposed(zero);
        }
        else
        {
            // the pointer exist
            // Since we only have 1 arg
            finalFunction->PushComposed(ChainRule(Func));
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
                        finalFunction->PushComposed(Derivative(Arg));
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
                    finalFunction->PushComposed(Derivative(Arg));
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
                            finalFunction->PushComposed(ProductRule(Arg));
                            // chain rule
                        }
                        else if (ptr->GetData() == "/")
                        {
                            finalFunction->PushComposed(QuotientRule(Arg));
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
            finalFunction->PushComposed(ChainRule(Func));
        }
    }
    return finalFunction;
}

std::shared_ptr<Function_Composed> derivative::ChainRule(std::shared_ptr<Function> Func_)
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
    auto Arg = std::make_shared<Function_Composed>();
    for (auto &a : Func->GetComposedData())
    {
        Arg->PushComposed(a);
    }
    FinalFunction->PushComposed(Derivative(Arg));
    if (Func->GetData() != "ComposedOperationSpecialNoInitalized")
    {
        std::shared_ptr<Function_Operation> multiple = std::make_shared<Function_Operation>();
        multiple->PushOperation("*");
        FinalFunction->PushComposed(multiple);
        FinalFunction->PushComposed(derivativeTable[Func->GetData()](Func));
    }
    return FinalFunction;
}
std::shared_ptr<Function_Composed> derivative::ProductRule(std::shared_ptr<Function> Func_)
{
    // Derivative class always assume that we have more than 3 args
    std::shared_ptr<Function_Composed> FinalFunction = std::make_shared<Function_Composed>();
    auto Func = std::dynamic_pointer_cast<Function_Composed>(Func_);
    if (!Func)
    {
        std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
        zero->PushOperation("0");
        FinalFunction->PushComposed(zero);
        return FinalFunction;
    }
    auto fx = Func->GetComposedData().at(0);
    auto gx = std::make_shared<Function_Composed>();
    for (int i = 3; i < Func->GetComposedData().size(); i++)
    {
        gx->PushComposed(Func->GetComposedData().at(i));
    }
    FinalFunction->PushComposed(Derivative(fx));
    std::shared_ptr<Function_Operation> multiple = std::make_shared<Function_Operation>();
    multiple->PushOperation("*");
    FinalFunction->PushComposed(multiple);
    FinalFunction->PushComposed(gx);
    std::shared_ptr<Function_Operation> addition = std::make_shared<Function_Operation>();
    addition->PushOperation("+");
    FinalFunction->PushComposed(addition);
    FinalFunction->PushComposed(Derivative(gx));
    std::shared_ptr<Function_Operation> multiple1 = std::make_shared<Function_Operation>();
    multiple1->PushOperation("*");
    FinalFunction->PushComposed(multiple1);
    FinalFunction->PushComposed(fx);
    return FinalFunction;
}
std::shared_ptr<Function_Composed> derivative::QuotientRule(std::shared_ptr<Function> Func_)
{
    std::shared_ptr<Function_Composed> FinalFunction = std::make_shared<Function_Composed>();
    auto Func = std::dynamic_pointer_cast<Function_Composed>(Func_);
    if (!Func)
    {
        std::shared_ptr<Function_Number> zero = std::make_shared<Function_Number>();
        zero->PushOperation("0");
        FinalFunction->PushComposed(zero);
        return FinalFunction;
    }
    auto gx = Func->GetComposedData().at(2);
    auto fx = std::make_shared<Function_Composed>();
    fx->PushComposed(Func->GetComposedData().at(0));
    for (int i = 3; i < Func->GetComposedData().size(); i++)
    {
        fx->PushComposed(Func->GetComposedData().at(i));
    }
    std::shared_ptr<Function_Composed> FinalFunctionUp = std::make_shared<Function_Composed>();
    FinalFunctionUp->PushComposed(Derivative(fx));
    std::shared_ptr<Function_Operation> multiple = std::make_shared<Function_Operation>();
    multiple->PushOperation("*");
    FinalFunctionUp->PushComposed(multiple);
    FinalFunctionUp->PushComposed(gx);
    std::shared_ptr<Function_Operation> minus = std::make_shared<Function_Operation>();
    minus->PushOperation("-");
    FinalFunctionUp->PushComposed(minus);
    FinalFunctionUp->PushComposed(Derivative(gx));
    std::shared_ptr<Function_Operation> multiple1 = std::make_shared<Function_Operation>();
    multiple1->PushOperation("*");
    FinalFunctionUp->PushComposed(multiple1);
    FinalFunctionUp->PushComposed(fx);
    std::shared_ptr<Function_Composed> PowDe = std::make_shared<Function_Composed>();
    PowDe->PushOperation("squared(");
    PowDe->PushComposed(gx);
    std::shared_ptr<Function_Operation> division = std::make_shared<Function_Operation>();
    division->PushOperation("/");
    FinalFunction->PushComposed(FinalFunctionUp);
    FinalFunction->PushComposed(division);
    FinalFunction->PushComposed(PowDe);
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