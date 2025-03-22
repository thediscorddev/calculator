#pragma once
#include "Function.hpp"
#include <string>
#include <vector>
class Function_Number: public Function
{
    private:
        std::string Number;
    public:
        Function_Operation();
        void PushOperation(std::string& Operation);
        std::string & GetData();
};