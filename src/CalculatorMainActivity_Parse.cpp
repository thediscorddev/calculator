#include "../scr/CalculatorMainActivity.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <map>
#include <string>
double CalculatorMainActivity::Calculate(int index)
{
    //Parser
    float CurrentNumPart = 0;
    int decimalNum = 0;
    int bracketLevel = 0;
    int Eid = 0;
    std::map<std::string,std::vector<std::string>> ValueList; //important
    std::vector<std::string> PlannedOperation;

    for(int i = index-1; i < CurrentInput.size(); i++)
    {
        const auto& a = CurrentInput.at(i);
        try
        {
            std::cout << a << std::endl;
            std::cout << i << std::endl;
            if(decimalNum == 0) CurrentNumPart=CurrentNumPart*10+std::stoi(a);
            else {
                int m = 1;
                for(int i = 0; i < decimalNum; i++)
                {
                    m*=10;
                }
                CurrentNumPart+=(float) std::stoi(a)/m;
                decimalNum++;
            }
        }
        catch(const std::exception& e)
        {
            // Not a number, possibly "*", "-", "+", "\", "sin("
            if(a == ".") {
                decimalNum = 1;
            }
            if(a == "+" || a == "-" || a == "*" || a == "/") {
                std::string o = a;
                PlannedOperation.push_back(std::to_string(CurrentNumPart));
                PlannedOperation.push_back(o);
                CurrentNumPart = 0;
                decimalNum = 0;
            }
        }
    }
    PlannedOperation.push_back(std::to_string(CurrentNumPart));
    CurrentNumPart = 0;
    decimalNum = 0;
    int ia = 0;
    bool mdStillAvailable = true;
    while(mdStillAvailable == true)
    {
        mdStillAvailable = false;
        if(ia >= PlannedOperation.size()) ia = 0;
        const auto& a = PlannedOperation.at(ia);
        if(a == "*" || a == "/")
        {
            if(ia -1 >= 0 && ia + 1 <= PlannedOperation.size())
            {
                try
                {
                    /* code */
                    std::string na = PlannedOperation.at(ia-1);
                    std::string nb = PlannedOperation.at(ia+1);
                    float fna = std::stof(na);
                    float fnb = std::stof(nb);
                    float resulta = 0;
                    if(a == "*")
                    {
                        resulta = fna*fnb;
                    }else if (a == "/" && fnb != 0) resulta = fna/fnb;
                    else if (a == "/" && fnb == 0) resulta = 999999;
                    PlannedOperation.erase(PlannedOperation.begin() + ia -1,PlannedOperation.begin() + ia + 2);
                    PlannedOperation.insert(PlannedOperation.begin() + ia - 1,std::to_string(resulta));
                    ia = 0;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
        ia++;
        for(const auto& a: PlannedOperation)
        {
            if(a == "*" || a == "/") mdStillAvailable = true;
        }
    }
    ia = 0;
    while(PlannedOperation.size() > 1)
    {
        if(ia >= PlannedOperation.size()) ia = 0;
        const auto& a = PlannedOperation.at(ia);
        if(a == "+" || a == "-")
        {
            if(ia -1 >= 0 && ia + 1 <= PlannedOperation.size())
            {
                try
                {
                    /* code */
                    std::string na = PlannedOperation.at(ia-1);
                    std::string nb = PlannedOperation.at(ia+1);
                    float fna = std::stof(na);
                    float fnb = std::stof(nb);
                    float resulta = 0;
                    if(a == "+")
                    {
                        resulta = fna+fnb;
                    }else if (a == "-") resulta = fna-fnb;
                    PlannedOperation.erase(PlannedOperation.begin() + ia -1,PlannedOperation.begin() + ia + 2);
                    PlannedOperation.insert(PlannedOperation.begin() + ia - 1,std::to_string(resulta));
                    ia = 0;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
        ia++;
    }
    return std::stod(PlannedOperation.at(0));
}