#include "../scr/Derivative.hpp"
#include <stdexcept>
std::shared_ptr<Function_Composed> Derivative::Derivative(std::shared_ptr<Function_Composed> Func)
{
    std::shared_ptr<Function_Composed> finalFunction = std::make_shared<Function_Composed>();
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
            finalFunction->PushComposed(Derivative(ptr));
            std::shared_ptr<Function_Operation> multiple = std::make_shared<Function_Operation>();
            multiple->PushOperation("*");
            finalFunction->PushComposed(multiple);
            finalFunction->PushComposed(ChainRule(Func->GetData(), ptr));
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
                    hasAddOrSubStract = true;
                    sign = ptr->GetData();
                    // clean the arg
                    Arg = std::make_shared<Function_Composed>();
                }
            }
            else
            {
                // What we did is just a bunch of * and / operation
                std::vector<int> NumberList;
                double newCOnstant = 1;
                for (int j = 0; j < 2; j++)
                {
                    for (int i = 0; i < Arg->GetComposedData().size(); i++)
                    {
                        auto ptr = std::dynamic_pointer_cast<Function_Operation>(Arg->GetComposedData().at(i));
                        if (ptr)
                        {
                            if (ptr->GetData() != "*")
                                continue;
                            // multiply operation
                            if (i == 0 || i == Arg->GetComposedData().size() - 1)
                                throw std::runtime_error("Out of bound");
                            auto ptr2 = std::dynamic_pointer_cast<Function_Number>(Arg->GetComposedData().at(i - 1));
                            auto ptr3 = std::dynamic_pointer_cast<Function_Number>(Arg->GetComposedData().at(i + 1));
                            if (ptr2)
                            {
                                try
                                {
                                    std::stod(ptr2->GetData());
                                    // constant
                                    if (NumberList.size() > 0)
                                        if (NumberList.at(NumberList.size() - 1) != i)
                                            NumberList.push_back(i-1);
                                }
                                catch (const std::exception &e)
                                {
                                }
                            }
                            if (ptr3)
                            {
                                try
                                {
                                    std::stod(ptr3->GetData());
                                    // constant
                                    if (NumberList.size() > 0)
                                        if (NumberList.at(NumberList.size() - 1) != i)
                                            NumberList.push_back(i+1);
                                }
                                catch (const std::exception &e)
                                {
                                }
                            }
                        }
                    }
                    for (int a : NumberList)
                    {
                        if (j == 0)
                            newCOnstant *= std::stod(std::dynamic_pointer_cast<Function_Number>(Arg->GetComposedData().at(a))->GetData());
                        else
                            newCOnstant = newCOnstant / std::stod(std::dynamic_pointer_cast<Function_Number>(Arg->GetComposedData().at(a))->GetData());
                    }
                    for (int a : NumberList)
                    {
                        Arg->GetComposedData().erase(Arg->GetComposedData().begin() + a);
                    }
                    NumberList.clear();
                }
                std::shared_ptr<Function_Number> C = std::make_shared<Function_Number>();
                C->PushOperation(std::to_string(newCOnstant));
                Arg->GetComposedData().insert(Arg->GetComposedData().begin(), newCOnstant);
                // we multiplied the constant
                // Now we have only division of the constant left
                //TODO: FIX THIS PATHENIC ALG
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
            finalFunction->PushComposed(Derivative(Arg));
            std::shared_ptr<Function_Operation> multiple = std::make_shared<Function_Operation>();
            multiple->PushOperation("*");
            finalFunction->PushComposed(multiple);
            finalFunction->PushComposed(ChainRule(Func->GetData(), ptr));
        }
    }
    return finalFunction;
}