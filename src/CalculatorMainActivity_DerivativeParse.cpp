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
Function_Composed CalculatorMainActivity::CalculateDerivative(Function_Composed & function)
{
    Function_Composed Output;
    std::vector<std::shared_ptr<Function>> argument = function.GetComposedData();
    std::string OutlineType = function.GetData();
    if(OutlineType == "ComposedOperationSpecialNoInitalized")
    {
        // Uninitalized outline function
        //That means we just past an arg, or there are multiple function in this call
        //I will handle it later on
    }else {
        //another function like squared, sin, cos,...
        //either way, we will apply chain rule first
        //Perhaps we should create another Function_Composed type first for the chain rule, except it is the arguments
        Function_Composed Arg;
        for(auto& el: argument)
        {
            Arg.PushComposed(el);
        }
        //Calculate the derivative of the arg
        std::vector<std::shared_ptr<Function>> ArgDev = CalculateDerivative(Arg);
        for(auto& el: ArgDev)
        {
            Output.PushComposed(el);
        }
        Function_Operation MultipleOperator;
        MultipleOperator.PushOperation("*");
        Output.PushComposed(MultipleOperator);
        std::vector<std::shared_ptr<Function>> OutlineDEV = CalculateDerivativeAndCreateNewOutLine(OutlineType,Arg); //make this function
        for(auto& el: OutlineDEV)
        {
            Output.PushComposed(el);
        }
        //Now that we have successfully calculated g'(x)*f'(g(x)) theorically
    }
    return Output;
}