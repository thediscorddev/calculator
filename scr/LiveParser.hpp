#pragma once
#include "Function_Composed.hpp"
#include <map>
#include <string>
#include <vector>
//The live parser is used to parse directly with button clicks and reduces change of misinterpert
class LiveParser
{
    //this shouldn't be a static class
    private:
        bool isNonNumeral = false;
        std::map<std::string, std::string> ArgList;
        std::vector<std::string> ExpressionList;
        int expressionId = 0;
        int position = 0;
    public:
        LiveParser(); //initalize parser
        void InstantlyParseFunction(std::string newInput);
        void ClearFunc();
        double CalculateOperation();
        Function_Composed getFunction(); //if isNonNumber is true
};