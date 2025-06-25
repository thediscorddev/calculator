#pragma once
#include "Function.hpp"
#include "Function_Number.hpp"
#include "FunctionAndConstantList.hpp"
#include <string>
#include <memory>
#include <vector>
class Function_Composed: public Function
{
    protected:
        std::vector<std::shared_ptr<Function>> ComposedList;
        std::vector<std::shared_ptr<Function>> OtherArg;
        std::string OutlineFunc;
        int Highlight = 0; // 0 = no, 1 = left most, 2 is whole, 3 is inner, 4 is right most, 5 is backet
        int ArgLvl = 0;
        bool DestroyLastBracket = false;
    public:
        void BreakBracket(bool Status = true);
        Function_Composed();
        void PushOperation(const std::string& Operation);
        void PushComposed(std::shared_ptr<Function> Composed);
        void PushComposed(std::vector<std::shared_ptr<Function>> Composed);
        std::string & GetData();
        std::vector<std::shared_ptr<Function>> & GetComposedData();
        bool ContainsUnknown();
        int getArgLvl();
        void setArgLvl(unsigned int lvl);
        Function_Number Calculate(double number = 0);
        std::string toString();
        std::string toLatexString();
        void highlight(int level);
};