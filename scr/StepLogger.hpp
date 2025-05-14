#pragma once
#include <string>
#include <vector>
class StepLogger
{
    private:
        static std::vector<std::string> Step;
    public:
        static void Clear();
        static void Append(std::string step);
        static std::vector<std::string> CopyStep();
};