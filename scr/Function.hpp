#pragma once
#include <string>
#include <vector>
class Function
{
protected:
    std::string Type; // function type, single var, multi var, operation,...
    std::string Label = "NoLabel";

public:
    Function();
    virtual void PushOperation(const std::string &Operation) = 0;
    std::string GetFunctionType();
    std::string Getlabel();
    void SetLabel(const std::string &label);
    virtual std::string &GetData() = 0;
};