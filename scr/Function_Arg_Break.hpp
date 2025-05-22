#pragma once
#include "Function.hpp"
class Function_Arg_Break : public Function
{
    private:
        std::string Number;
    public:
        Function_Arg_Break();
        void PushOperation(const std::string &Operation);
        std::string &GetData();
};