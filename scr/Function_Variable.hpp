#pragma once
#include "Function.hpp"
#include <string>
#include <vector>
class Function_Variable: public Function
{
    private:
        std::string Number;
    public:
        Function_Variable();
        void PushOperation(const std::string& Operation);
        std::string & GetData();
};