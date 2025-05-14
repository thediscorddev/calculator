#pragma once
#include "Function.hpp"
#include <string>
#include <vector>
class Function_Operation: public Function
{
    private:
        std::string OperationType;
    public:
        Function_Operation();
        void PushOperation(const std::string& Operation);
        std::string & GetData();
};