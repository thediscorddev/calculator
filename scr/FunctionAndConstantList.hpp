#pragma once
#include <vector>
#include <functional>
#include <map>
#include <string>
class FunctionAndConstantList
{
    public:
        static std::map<std::string, double> constantList;
        static std::map<std::string, std::function<double(double)>> FunctionOneVar;
};