#include "../scr/CalculatorMainActivity.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <memory>
#include "../scr/Function.hpp"
#include "../scr/Function_Number.hpp"
#include "../scr/Function_Composed.hpp"
#include "../scr/Function_Operation.hpp"

Function_Composed CalculatorMainActivity::CalculateDerivativeAndCreateNewOutLine(std::string OutlineType, std::shared_ptr<Function> Arg)
{
    Function_Composed Output;
    if(OutlineType == "tan")
    {
        Function_Composed Derivative_;
        Output.PushOperation("squared");
        Derivative_.PushOperation("sec");
        Derivative_.PushComposed(Arg);
        Output.PushComposed(std::make_shared<Function_Composed>(Derivative_));
        
    }else if(OutlineType == "sec")
    {
        Function_Composed Derivative;
        Function_Composed Derivative_;
        Derivative.PushOperation("tan");
        Derivative_.PushOperation("sec");
        Derivative.PushComposed(Arg);
        Derivative_.PushComposed(Arg);
        std::shared_ptr<Function_Operation> MultipleOperator = std::make_shared<Function_Operation>();
        std::string oper = "*";
        MultipleOperator->PushOperation(oper);
        Output.PushComposed(std::make_shared<Function_Composed>(Derivative_));
        Output.PushComposed(MultipleOperator);
        Output.PushComposed(std::make_shared<Function_Composed>(Derivative));
        //sec(u) *tan(u)
    }else if(OutlineType == "ln")
    {
        Function_Number Number_;
        std::string oper_ = "1";
        Number_.PushOperation(oper_);
        std::shared_ptr<Function_Operation> DivisOperator = std::make_shared<Function_Operation>();
        std::string oper = "/";
        DivisOperator->PushOperation(oper);
        Output.PushComposed(std::make_shared<Function_Number>(Number_));
        Output.PushComposed(DivisOperator);
        Output.PushComposed(Arg); 
        // 1/u
    }else if(OutlineType == "sin")
    {
        Output.PushOperation("cos");
        Output.PushComposed(Arg);
        //cos(u)
    }else if(OutlineType == "sinh")
    {
        Output.PushOperation("cosh");
        Output.PushComposed(Arg);
    }else if(OutlineType == "cosh")
    {
        Output.PushOperation("sinh");
        Output.PushComposed(Arg);
    }else if(OutlineType == "exp")
    {
        Output.PushOperation("exp");
        Output.PushComposed(Arg);
    }
    //more
    //I've already handle the Arg derivative tho.
    return Output;
}