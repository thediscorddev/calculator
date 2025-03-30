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
Function_Composed CalculatorMainActivity::CalculateDerivative(Function_Composed &function)
{
    Function_Composed Output;
    std::vector<std::shared_ptr<Function>> argument = function.GetComposedData();
    std::string OutlineType = function.GetData();
    if (OutlineType == "ComposedOperationSpecialNoInitalized")
    {
        // Uninitalized outline function
        // That means we just past an arg, or there are multiple function in this call
        // I will handle it later on
        // I should check if it is quotient rule, or chain rule
        // Either way, the best next step is to loop
        // For product and quotient rule, there should be a 3 funciton * list, or just it
        int i = 0;
        while(i < argument.size())
        {
            std::shared_ptr<Function> current_func = argument.at(i);
            if(current_func->GetFunctionType() == "Number")
            {
                std::string arg_ = ((Function_Operation*)current_func.get())->GetData();
                try
                {
                    std::stod(arg_);
                    // surely a number
                    // Process like this: If the next arg is an operation and it is + or -? the derivative of this is 0
                    // If it is * or / ? Then the derivative could be
                    //c * f'(x) or if it is c*a? it is 0
                    // if it is the end of function? Then we simply just return 0
                    i++;
                    // increase I variable
                    if(i < argument.size())
                    {
                        if(argument.at(i)->GetFunctionType() == "Operation")
                        {
                            arg_ = ((Function_Operation*)argument.at(i).get())->GetData();
                            if(arg_ == "+" || arg_ == "-")
                            {
                                //addition
                                //since this is addition, we will ignore it
                                i++;
                            }else if (arg_ == "*" || arg_ == "/")
                            {
                                //not addition or substraction, there is a chance that the next arg will be a function
                                //Let's just assume it for now
                                Function_Operation Arg;
                            }
                        }
                    }else {
                        //This is a number but no extra arg coming after it
                        // I should handle edge case to make sure a*f(x)_c is the same as a*c*f(x), otherwise c will be treated as 0 and thus cancel out the whole function
                        //but for now..
                    }
                }
                catch(const std::exception& e)
                {
                    //not a number or a constant, variable
                    if(constantList.find(arg_) != constantList.end())
                    {
                        //a constant, process normally
                    }else {
                        // variables like x, y or z,..
                    }
                }
                
            }
        }
    }
    else
    {
        // another function like squared, sin, cos,...
        // either way, we will apply chain rule first
        // Perhaps we should create another Function_Composed type first for the chain rule, except it is the arguments
        Function_Composed Arg;
        for (auto &el : argument)
        {
            Arg.PushComposed(el);
        }
        // Calculate the derivative of the arg
        std::vector<std::shared_ptr<Function>> ArgDev = CalculateDerivative(Arg).GetComposedData();
        for (auto &el : ArgDev)
        {
            Output.PushComposed(el);
        }
        std::shared_ptr<Function_Operation> MultipleOperator = std::make_shared<Function_Operation>();
        std::string oper = "*";
        MultipleOperator->PushOperation(oper);
        Output.PushComposed(MultipleOperator);
        Function_Composed OutlineDEV = CalculateDerivativeAndCreateNewOutLine(OutlineType, std::make_shared<Function_Composed>(Arg)); // make this function
        for (auto &el : OutlineDEV.GetComposedData())
        {
            Output.PushComposed(el);
        }
        // Now that we have successfully calculated g'(x)*f'(g(x)) theorically
    }
    return Output;
}