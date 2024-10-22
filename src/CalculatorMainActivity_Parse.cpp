#include "../scr/CalculatorMainActivity.hpp"
#include <stdexcept>
#include <iostream>
double CalculatorMainActivity::Calculate(int index)
{
    //Parser
    int CurrentNumPart = 0;
    int decimalNum = 1;
    bool IsDecimalPart = false;
    for(int i = index-1; i < CurrentInput.size(); i++)
    {
        const auto& a = CurrentInput.at(i);
        try
        {
            std::cout << a << std::endl;
            std::cout << i << std::endl;
            if(IsDecimalPart == false) CurrentNumPart=CurrentNumPart*10+std::stoi(a);
            else {
                int m = 1;
                for(int i = 0; i < decimalNum; i++)
                {
                    m*=10;
                }
                CurrentNumPart+=std::stoi(a)/m;
                decimalNum++;
            }
        }
        catch(const std::exception& e)
        {
            // Not a number, possibly "*", "-", "+", "\", "sin("
            if(a == ".") {
                IsDecimalPart = true;
            }
            if(a == "+") return CurrentNumPart+Calculate(i+2);
            if(a == "-") return CurrentNumPart-Calculate(i+2);
            if(a == "*") return CurrentNumPart*Calculate(i+2);
            if(a == "/") return CurrentNumPart/Calculate(i+2);
            if(a == ")") return CurrentNumPart;
            if(a == "(") continue;
        }
    }
    return CurrentNumPart;
}