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
        static void Append(std::string Text, std::string latex, int level = 0, bool display = true);
        static void Append(std::string Text1, std::string Text2, std::string latex, int level = 0, bool display = true);
        static std::vector<std::string> CopyStep();
};