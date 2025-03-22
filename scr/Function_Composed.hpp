#pragma once
#include "Function.hpp"
#include <string>
#include <memory>
#include <vector>
class Function_Composed: public Function
{
    private:
        std::vector<std::shared_ptr<Function>> ComposedList;
        std::string OutlineFunc;
    public:
        Function_Operation();
        void PushOperation(std::string& Operation);
        void PushComposed(std::shared_ptr<Function> Composed);
        std::string & GetData();
        std::vector<std::shared_ptr<Function>> & GetComposedData();
};