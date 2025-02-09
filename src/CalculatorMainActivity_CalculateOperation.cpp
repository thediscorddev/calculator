#include <vector>
#include <string>
#include "../scr/CalculatorMainActivity.hpp"
std::vector<std::string> CalculatorMainActivity::CalculateOperation(std::vector<std::string> PlannedOperation_)
{
    int ia = 0;
    bool mdStillAvailable = true;
    while(mdStillAvailable == true)
    {
        mdStillAvailable = false;
        if(ia >= PlannedOperation_.size()) ia = 0;
        const auto& a = PlannedOperation_.at(ia);
        if(a == "*" || a == "/")
        {
            if(ia -1 >= 0 && ia + 1 <= PlannedOperation_.size())
            {
                try
                {
                    /* code */
                    std::string na = PlannedOperation_.at(ia-1);
                    std::string nb = PlannedOperation_.at(ia+1);
                    float fna = std::stof(na);
                    float fnb = std::stof(nb);
                    float resulta = 0;
                    if(a == "*")
                    {
                        resulta = fna*fnb;
                    }else if (a == "/" && fnb != 0) resulta = fna/fnb;
                    else if (a == "/" && fnb == 0) resulta = 999999;
                    PlannedOperation_.erase(PlannedOperation_.begin() + ia -1,PlannedOperation_.begin() + ia + 2);
                    PlannedOperation_.insert(PlannedOperation_.begin() + ia - 1,ToStringWithPrecision(resulta));
                    ia = 0;
                }
                catch(const std::exception& e)
                {
                    return PlannedOperation_;
                }
            }
        }
        ia++;
        for(const auto& a: PlannedOperation_)
        {
            if(a == "*" || a == "/") mdStillAvailable = true;
        }
    }
    ia = 0;
    while(PlannedOperation_.size() > 1)
    {
        if(ia >= PlannedOperation_.size()) ia = 0;
        const auto& a = PlannedOperation_.at(ia);
        if(a == "+" || a == "-")
        {
            if(ia -1 >= 0 && ia + 1 <= PlannedOperation_.size())
            {
                try
                {
                    /* code */
                    std::string na = PlannedOperation_.at(ia-1);
                    std::string nb = PlannedOperation_.at(ia+1);
                    float fna = std::stof(na);
                    float fnb = std::stof(nb);
                    float resulta = 0;
                    if(a == "+")
                    {
                        resulta = fna+fnb;
                    }else if (a == "-") resulta = fna-fnb;
                    PlannedOperation_.erase(PlannedOperation_.begin() + ia -1,PlannedOperation_.begin() + ia + 2);
                    PlannedOperation_.insert(PlannedOperation_.begin() + ia - 1,ToStringWithPrecision(resulta));
                    ia = 0;
                }
                catch(const std::exception& e)
                {
                    return PlannedOperation_;
                }
            }
        }
        ia++;
    }
    return PlannedOperation_;
}