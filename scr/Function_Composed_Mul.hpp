#pragma once
#include "Function_Composed.hpp"
class Function_Composed_Mul: public Function_Composed
{
    protected:
        //
        int argLevel = 0; // first arg
        std::vector<std::shared_ptr<Function_Composed>> ArgList;
    public:
        int setArg(int lvl);
        std::vector<std::shared_ptr<Function_Composed>> * GetArg();
        Function_Composed_Mul(); //constructor
        void PushOperation(const std::string& Operation);
        void PushComposed(std::shared_ptr<Function> Composed);
        void PushComposed(std::vector<std::shared_ptr<Function>> Composed);
        std::vector<std::shared_ptr<Function>> & GetComposedData(int lvl);
        int GetArgCount();
};