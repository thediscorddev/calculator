#include "../scr/CalculatorMainActivity.hpp"
#include "../scr/Function_Operation.hpp"
#include "../scr/Function_Composed.hpp"
#include "../scr/Function_Number.hpp"
#include <stdexcept>
#include <iostream>
#include "../scr/StepLogger.hpp"
#include <vector>
#include <map>
#include <string>
#include "../scr/Derivative.hpp"
#include <stdexcept>
#include "../scr/MathWindow.hpp"
static std::vector<int> FinishedId;
std::shared_ptr<Function> CalculatorMainActivity::GetCurrentPosition(std::shared_ptr<Function_Composed> func, int id, bool Create)
{
    return GetCurrentPosition_(func, id, Create).func;
}
FunctionReturn CalculatorMainActivity::GetCurrentPosition_(std::shared_ptr<Function_Composed> func, int id, bool Create)
{
    FunctionReturn Data;
    int cid = id - 1;
    if (id <= 0)
    {
        Data.IsNull = false;
        Data.func = func;
        return Data;
    }

    auto &list = func->GetComposedData();
    for (auto &a : list)
    {
        if (a->Getlabel() == "__id_" + std::to_string(id))
        {
            Data.IsNull = false;
            Data.func = a;
            return Data;
        }
        else
        {
            auto ptr = std::dynamic_pointer_cast<Function_Composed>(a);
            if (ptr)
            {
                // a function composed
                FunctionReturn Data = GetCurrentPosition_(ptr, id, false);
                if (Data.IsNull == false)
                    return Data;
            }
        }
        // No returning
        // We might as well check if it would return anything
    }

    // Recurse to create the previous level
    // Other function stay inside should be at
    //
    if (!Create)
    {
        return Data;
    }
    // This case is where we were told to create
    // To create, assuming the func has not finished yet
    bool conflict = true;
    while (conflict)
    {
        conflict = false;
        for (const auto &a : FinishedId)
        {
            if (a == cid)
            {
                conflict = true;
                cid--;
            }
        }
    }
    std::shared_ptr<Function_Composed> currentPosition = std::dynamic_pointer_cast<Function_Composed>(
        GetCurrentPosition(func, cid));

    if (!currentPosition)
    {
        throw std::runtime_error("Invalid function hierarchy: expected Function_Composed");
    }

    auto newComposed = std::make_shared<Function_Composed>();
    newComposed->SetLabel("__id_" + std::to_string(id));
    currentPosition->PushComposed(newComposed);
    Data.IsNull = false;
    Data.func = newComposed;
    return Data;
}

double CalculatorMainActivity::Calculate(int index)
{
    FinishedId.clear();
    // Parser
    float CurrentNumPart = 0;
    bool HasPush = false;
    int decimalNum = 0;
    int bracketLevel = 0;
    int Hid = 0;
    int CurrentId = 0;
    std::map<std::string, std::vector<std::string>> ValueList; // important
    std::map<std::string, bool> CalculatedValueList;           // important
    std::map<std::string, std::string> Ftype;                  // important
    std::vector<std::string> PlannedOperation;
    std::shared_ptr<Function_Composed> FullFunction = std::make_shared<Function_Composed>();

    for (int i = index - 1; i < CurrentInput.size(); i++)
    {
        const auto &a = CurrentInput.at(i);
        try
        {
            if (decimalNum == 0)
                CurrentNumPart = CurrentNumPart * 10 + std::stoi(a);
            else
            {
                int m = 1;
                for (int i = 0; i < decimalNum; i++)
                {
                    m *= 10;
                }
                CurrentNumPart += (float)std::stoi(a) / m;
                decimalNum++;
            }
            HasPush = true;
        }
        catch (const std::exception &e)
        {
            // Not a number, possibly "*", "-", "+", "\", "sin("
            if (a == ".")
            {
                decimalNum = 1;
            }
            else if (a == "x")
            {
                std::shared_ptr<Function> number_ = std::make_shared<Function_Variable>();
                number_->PushOperation(a);
                std::shared_ptr<Function> number = std::make_shared<Function_Number>();
                std::shared_ptr<Function> op = std::make_shared<Function_Operation>();
                op->PushOperation("*");
                number->PushOperation(ToStringWithPrecision(CurrentNumPart));
                if (CurrentId == 0)
                {
                    if (HasPush == true)
                    {
                        FullFunction->PushComposed(number);
                        FullFunction->PushComposed(op);
                    }
                    FullFunction->PushComposed(number_);
                }
                else
                {
                    auto pos_ = std::dynamic_pointer_cast<Function_Composed>(GetCurrentPosition(FullFunction, CurrentId));
                    if (HasPush == true)
                    {
                        pos_->PushComposed(number);
                        pos_->PushComposed(op);
                    }
                    pos_->PushComposed(number_);
                }
                CurrentNumPart = 0;
                HasPush = false;
                decimalNum = 0;
            }
            else if (a == "+" || a == "-" || a == "*" || a == "/")
            {
                std::shared_ptr<Function> number = std::make_shared<Function_Number>();
                std::shared_ptr<Function> op = std::make_shared<Function_Operation>();
                op->PushOperation(a);
                number->PushOperation(ToStringWithPrecision(CurrentNumPart));
                std::string o = a;
                if (CurrentId == 0)
                {
                    if (HasPush == true)
                        FullFunction->PushComposed(number);
                    FullFunction->PushComposed(op);
                }
                else
                {
                    auto pos_ = std::dynamic_pointer_cast<Function_Composed>(GetCurrentPosition(FullFunction, CurrentId));
                    if (HasPush == true)
                    {
                        pos_->PushComposed(number);
                    }
                    pos_->PushComposed(op);
                }
                CurrentNumPart = 0;
                HasPush = false;
                decimalNum = 0;
            }
            else if (constantList.find(a) != constantList.end())
            {
                std::shared_ptr<Function> number = std::make_shared<Function_Number>();
                std::shared_ptr<Function> Const = std::make_shared<Function_Number>();
                std::shared_ptr<Function> mul = std::make_shared<Function_Operation>();
                mul->PushOperation("*");
                number->PushOperation(ToStringWithPrecision(CurrentNumPart));
                Const->PushOperation(ToStringWithPrecision(constantList[a]));
                if (CurrentId == 0)
                {
                    if (HasPush == true)
                    {
                        FullFunction->PushComposed(number);
                        FullFunction->PushComposed(mul);
                    }
                    FullFunction->PushComposed(Const);
                }
                else
                {
                    auto pos_ = std::dynamic_pointer_cast<Function_Composed>(GetCurrentPosition(FullFunction, CurrentId));
                    if (HasPush == true)
                    {
                        pos_->PushComposed(number);
                        pos_->PushComposed(mul);
                    }
                    FullFunction->PushComposed(Const);
                }
                CurrentNumPart = 0;
                HasPush = false;
                decimalNum = 0;
            }
            else if (a == "(" || a != ")")
            {
                // KEEP AN EYE
                Hid++;
                CurrentId = Hid;
                auto pos_ = std::dynamic_pointer_cast<Function_Composed>(GetCurrentPosition(FullFunction, CurrentId));
                if (a != "(")
                    pos_->PushOperation(a);
            }
            else if (a == ")")
            {
                auto pos_ = std::dynamic_pointer_cast<Function_Composed>(GetCurrentPosition(FullFunction, CurrentId));
                std::shared_ptr<Function> number = std::make_shared<Function_Number>();
                number->PushOperation(ToStringWithPrecision(CurrentNumPart));
                if (HasPush == true)
                    pos_->PushComposed(number);
                CurrentNumPart = 0;
                HasPush = false;
                decimalNum = 0;
                FinishedId.push_back(CurrentId);
                bool conflict = true;
                while (conflict)
                {
                    conflict = false;
                    for (const auto &a : FinishedId)
                    {
                        if (a == CurrentId)
                        {
                            conflict = true;
                            CurrentId--;
                        }
                    }
                }
            }
        }
    }
    if (CurrentId != 0)
    {
        // error
        throw std::runtime_error("Syntax Error");
    }
    std::shared_ptr<Function> number = std::make_shared<Function_Number>();
    number->PushOperation(ToStringWithPrecision(CurrentNumPart));
    if (HasPush == true)
        FullFunction->PushComposed(number);
    CurrentNumPart = 0;
    HasPush = false;
    decimalNum = 0;
    bool hasDoneDefiningValue = false;
    /*while (hasDoneDefiningValue != true)
    {
        hasDoneDefiningValue = true;
        // This loop run unitl the value list is solved
        for (int i = 1; i <= Hid; i++)
        {
            if (CalculatedValueList.find("__id_" + ToStringWithPrecision(i)) == CalculatedValueList.end())
            {
                // Not fully resolved
                bool FullyResolvedConstant = true;
                for (int el_el = 0; el_el < ValueList["__id_" + ToStringWithPrecision(i)].size(); el_el++)
                {
                    const auto &el__ = ValueList["__id_" + ToStringWithPrecision(i)].at(el_el);
                    try
                    {
                        std::stod(el__); // check if it is a number
                    }
                    catch (const std::exception &e)
                    {
                        if (el__ != "+" && el__ != "-" && el__ != "*" && el__ != "/")
                        {
                            // ID or a function bracket
                            hasDoneDefiningValue = false;
                            if (CalculatedValueList.find(el__) == CalculatedValueList.end())
                            {
                                FullyResolvedConstant = false;
                            }
                            else
                            {
                                ValueList["__id_" + ToStringWithPrecision(i)].at(el_el) = ValueList[el__].at(0);
                            }
                        }
                    }
                }
                if (FullyResolvedConstant == true)
                {
                    CalculatedValueList["__id_" + ToStringWithPrecision(i)] = true;
                    // Perhaps it is time to solve this:
                    if (Ftype["__id_" + ToStringWithPrecision(i)] == "normal")
                        ValueList["__id_" + ToStringWithPrecision(i)] = CalculateOperation(ValueList["__id_" + ToStringWithPrecision(i)]);
                    else
                    {
                        std::vector<std::string> Temp_Vec;
                        try
                        {
                            std::string st_d = ValueList[el__].at(0);
                            while(ValueList.find(st_d) != ValueList.end()) {
                                st_d = ValueList[st_d].at(0);
                            }
                            Temp_Vec.push_back(ToStringWithPrecision(FunctionBatchOne[Ftype["__id_" + ToStringWithPrecision(i)]](std::stod(CalculateOperation(ValueList["__id_" + ToStringWithPrecision(i)]).at(0)))));
                            ValueList["__id_" + ToStringWithPrecision(i)] = Temp_Vec;
                        }
                        catch (std::exception &e)
                        {
                            std::cout << e.what() << std::endl;
                            throw std::runtime_error(e.what());
                        }
                    }
                }
            }
        }
    }
    for (int el_el = 0; el_el < PlannedOperation.size(); el_el++)
    {
        const auto &el__ = PlannedOperation.at(el_el);
        try
        {
            //
            std::stod(el__); // check if it is a number
        }
        catch (const std::exception &e)
        {
            if (el__ != "+" && el__ != "-" && el__ != "*" && el__ != "/")
            {
                std::string st_d = ValueList[el__].at(0);
                while (ValueList.find(st_d) != ValueList.end())
                {
                    st_d = ValueList[st_d].at(0);
                }
                // if(Ftype[el__] == "normal")
                PlannedOperation.at(el_el) = st_d;
            }
        }
    }

    std::vector<std::string> NewValues = CalculateOperation(PlannedOperation);
    if (NewValues.size() != 1)
    {
        // Error
    }
    */
    // return std::stod(NewValues.at(0));
    if (FullFunction->ContainsUnknown())
    {
        StepLogger::Clear();
        StepLogger::Append("\\begin{array}{l}");
        auto deri = derivative::Derivative(FullFunction);
        StepLogger::Append("So the derivative of:", FullFunction->toLatexString(),0);
        StepLogger::Append("Is:", deri->toLatexString(),0);
        StepLogger::Append("\\end{array}");
        auto* win = new MathWindow(nullptr);
        win->Show();
        return 12;
    }
    return std::stod(FullFunction->Calculate().GetData());
}
/*

*/