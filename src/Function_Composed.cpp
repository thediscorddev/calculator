#include "../scr/Function_Composed.hpp"
#include "../scr/Function_Operation.hpp"
#include "../scr/Function_Variable.hpp"
#include <stdexcept>
Function_Composed::Function_Composed()
{
    Type = "Composed";
    OutlineFunc = "ComposedOperationSpecialNoInitalized";
}
void Function_Composed::PushOperation(const std::string &Operation)
{
    OutlineFunc = Operation;
}
void Function_Composed::PushComposed(std::shared_ptr<Function> Composed)
{
    ComposedList.push_back(Composed);
}
std::string Function_Composed::toString()
{
    std::string originalStr = "";
    if (OutlineFunc != "ComposedOperationSpecialNoInitalized")
        originalStr += OutlineFunc;
    for (const auto &a : ComposedList)
    {
        auto ptr = std::dynamic_pointer_cast<Function_Composed>(a);
        if (ptr != nullptr)
        {
            if (ptr->GetData() == "ComposedOperationSpecialNoInitalized")
            {
                std::string display = ptr->toString();
                if (display != "")
                {
                    originalStr += "(" + display + ")";
                }
            }
            else
            {
                std::string display = ptr->toString();
                if (display != "")
                {
                    originalStr += display;
                }
            }
        }
        else
        {
            originalStr += a->GetData();
        }
    }
    if (OutlineFunc != "ComposedOperationSpecialNoInitalized")
        originalStr += ")";
    return originalStr;
}
std::string Function_Composed::toLatexString()
{
    std::string fullstring = "";
    int i = 0;
    if (OutlineFunc != "ComposedOperationSpecialNoInitalized")
    {
        if (OutlineFunc != "squared(" && OutlineFunc != "sqrt(")
            fullstring += OutlineFunc + "{";
        else if (OutlineFunc == "sqrt(")
            fullstring += "\\sqrt{";
        else
            fullstring += "({";
    }
    while (i < ComposedList.size())
    {
        auto element = ComposedList.at(i);
        if (i + 2 < ComposedList.size())
        {
            auto elptr = ComposedList.at(i + 1);
            auto elptr2 = ComposedList.at(i + 2);
            auto OperationPtr = std::dynamic_pointer_cast<Function_Operation>(elptr);
            if (OperationPtr)
            {
                if (OperationPtr->GetData() == "/")
                {
                    fullstring += "\\frac{";
                    auto COmposedel = std::dynamic_pointer_cast<Function_Composed>(element);
                    auto COmposedel2 = std::dynamic_pointer_cast<Function_Composed>(elptr2);
                    if (COmposedel)
                    {
                        // A composed
                        fullstring += COmposedel->toLatexString();
                    }
                    else
                    {
                        fullstring += element->GetData();
                    }
                    fullstring += "}{";
                    if (COmposedel2)
                    {
                        fullstring += COmposedel2->toLatexString();
                    }
                    else
                    {
                        fullstring += elptr2->GetData();
                    }
                    fullstring += "}";
                    i += 3;
                    continue;
                }
            }
            // Typical rendering
            // We will render it
        }
        auto ComposedEl = std::dynamic_pointer_cast<Function_Composed>(element);
        if (ComposedEl)
        {
            if (i > 0)
            {
                auto FuncOP = std::dynamic_pointer_cast<Function_Operation>(ComposedList.at(i - 1));
                if (FuncOP)
                {
                    if (FuncOP->GetData() == "*")
                    {
                        if (ComposedEl->GetData() == "ComposedOperationSpecialNoInitalized")
                        {
                            fullstring += "({";
                            fullstring += ComposedEl->toLatexString();
                            fullstring += "})";
                        }
                        else
                        {
                            fullstring += ComposedEl->toLatexString();
                        }
                    }
                    else
                    {
                        fullstring += ComposedEl->toLatexString();
                    }
                }
                else
                {
                    fullstring += ComposedEl->toLatexString();
                }
            }
            else
            {
                fullstring += ComposedEl->toLatexString();
            }
        }
        else
        {
            auto ptr_ = std::dynamic_pointer_cast<Function_Operation>(element);
            if (ptr_)
            {
                if (ptr_->GetData() == "*")
                {
                    fullstring += " \\cdot ";
                }
                else
                {
                    fullstring += element->GetData();
                }
            }
            else
            {
                fullstring += element->GetData();
            }
        }
        i++;
    }
    if (OutlineFunc != "ComposedOperationSpecialNoInitalized" && OutlineFunc != "sqrt(")
        fullstring += "})";
    if (OutlineFunc == "sqrt(")
        fullstring += "}";
    if (OutlineFunc == "squared(")
        fullstring += "^2";
    return fullstring;
}
void Function_Composed::PushComposed(std::vector<std::shared_ptr<Function>> Composed)
{
    for (auto &a : Composed)
    {
        ComposedList.push_back(a);
    }
}
std::string &Function_Composed::GetData()
{
    return OutlineFunc;
}
std::vector<std::shared_ptr<Function>> &Function_Composed::GetComposedData()
{
    return ComposedList;
}
bool Function_Composed::ContainsUnknown()
{
    for (const auto &a : ComposedList)
    {
        auto ptr = std::dynamic_pointer_cast<Function_Composed>(a);
        if (ptr != nullptr)
        {
            if (ptr->ContainsUnknown())
                return true;
        }
        auto ptr1 = std::dynamic_pointer_cast<Function_Variable>(a);
        if (ptr1 != nullptr)
            return true;
    }
    return false;
}
Function_Number Function_Composed::Calculate()
{
    Function_Number finalNumber;
    std::vector<std::string> OperationList;
    int i = 0;
    while (i < ComposedList.size())
    {
        auto ptr = std::dynamic_pointer_cast<Function_Composed>(ComposedList.at(i));
        if (ptr)
        {
            Function_Number Result = ptr->Calculate();
            OperationList.push_back(Result.GetData());
        }
        auto ptr1 = std::dynamic_pointer_cast<Function_Number>(ComposedList.at(i));
        if (ptr1)
        {
            // A single number
            if (OperationList.size() > 0)
            {
                std::string LastElement = OperationList.at(OperationList.size() - 1);
                try
                {
                    std::stod(LastElement);
                    // a number
                    OperationList.push_back("*");
                }
                catch (const std::exception &e)
                {
                    // Not a number
                }
            }
            try
            {
                std::stod(ptr1->GetData());
                // A number
                OperationList.push_back(ptr1->GetData());
            }
            catch (const std::exception &e)
            {
                // An unknown.. or a variable
                OperationList.push_back("0");
            }
        }
        auto ptr2 = std::dynamic_pointer_cast<Function_Operation>(ComposedList.at(i));
        if (ptr2)
        {
            // AN operation like +, -, *, /
            OperationList.push_back(ptr2->GetData());
        }
        i++;
    }
    // We have arrived, now it is time to reduce
    while (true)
    {
        // Reduce these number
        bool StillHasSpecial = false;
        int i = 0;
        while (i < OperationList.size())
        {
            std::string Element = OperationList.at(i);
            if (Element == "*")
            {
                StillHasSpecial = true;
                if (i <= 0 || i >= OperationList.size() - 1)
                    throw std::runtime_error("Syntax error");
                std::string ElementL = OperationList.at(i - 1);
                std::string ElementF = OperationList.at(i + 1);
                try
                {
                    double a = std::stod(ElementL);
                    double b = std::stod(ElementF);
                    double c = a * b;
                    OperationList.erase(OperationList.begin() + (i - 1), OperationList.begin() + (i + 2));
                    // Insert the new value at the old i-1 position
                    OperationList.insert(OperationList.begin() + (i - 1), std::to_string(c));
                }
                catch (const std::exception &e)
                {
                    throw std::runtime_error("Syntax error");
                }

                break;
            }
            else if (Element == "/")
            {
                StillHasSpecial = true;
                if (i <= 0 || i >= OperationList.size() - 1)
                    throw std::runtime_error("Syntax error");
                if (OperationList.at(i + 1) == "0")
                    throw std::runtime_error("Math error");
                std::string ElementL = OperationList.at(i - 1);
                std::string ElementF = OperationList.at(i + 1);
                try
                {
                    double a = std::stod(ElementL);
                    double b = std::stod(ElementF);
                    double c = a / b;
                    OperationList.erase(OperationList.begin() + (i - 1), OperationList.begin() + (i + 2));
                    // Insert the new value at the old i-1 position
                    OperationList.insert(OperationList.begin() + (i - 1), std::to_string(c));
                }
                catch (const std::exception &e)
                {
                    throw std::runtime_error("Syntax error");
                }
                break;
            }
            i++;
        }
        if (StillHasSpecial == false)
            break;
    }
    while (OperationList.size() > 1)
    {
        int i = 0;
        while (i < OperationList.size())
        {
            std::string Element = OperationList.at(i);
            if (Element == "+")
            {
                if (i <= 0 || i >= OperationList.size() - 1)
                    throw std::runtime_error("Syntax error");
                std::string ElementL = OperationList.at(i - 1);
                std::string ElementF = OperationList.at(i + 1);
                try
                {
                    double a = std::stod(ElementL);
                    double b = std::stod(ElementF);
                    double c = a + b;
                    OperationList.erase(OperationList.begin() + (i - 1), OperationList.begin() + (i + 2));
                    // Insert the new value at the old i-1 position
                    OperationList.insert(OperationList.begin() + (i - 1), std::to_string(c));
                }
                catch (const std::exception &e)
                {
                    throw std::runtime_error("Syntax error");
                }

                break;
            }
            else if (Element == "-")
            {
                if (i <= 0 || i >= OperationList.size() - 1)
                    throw std::runtime_error("Syntax error");
                std::string ElementL = OperationList.at(i - 1);
                std::string ElementF = OperationList.at(i + 1);
                try
                {
                    double a = std::stod(ElementL);
                    double b = std::stod(ElementF);
                    double c = a - b;
                    OperationList.erase(OperationList.begin() + (i - 1), OperationList.begin() + (i + 2));
                    // Insert the new value at the old i-1 position
                    OperationList.insert(OperationList.begin() + (i - 1), std::to_string(c));
                }
                catch (const std::exception &e)
                {
                    throw std::runtime_error("Syntax error");
                }
                break;
            }
            i++;
        }
    }
    // Now that the element only has 1 number
    if (OutlineFunc == "ComposedOperationSpecialNoInitalized")
    {
        finalNumber.PushOperation(OperationList.at(0));
    }
    else
    {
        double num = FunctionAndConstantList::FunctionOneVar[OutlineFunc](std::stod(OperationList.at(0)));
        finalNumber.PushOperation(std::to_string(num));
    }
    return finalNumber;
}
void Function_Composed::highlight(int level)
{
    Highlight = level;
}