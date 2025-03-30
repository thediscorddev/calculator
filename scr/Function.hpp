#pragma once
#include <string>
#include <vector>
class Function
{
    protected:
        std::string Type; //function type, single var, multi var, operation,...
    public:
        Function();
        virtual void PushOperation(std::string& Operation) = 0;
        std::string GetFunctionType();

};