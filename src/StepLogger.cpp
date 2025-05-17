#include "../scr/StepLogger.hpp"
static int counter = 1;
std::vector<std::string> StepLogger::Step;
void StepLogger::Clear() {
    counter=1;
    Step.clear();
};
void StepLogger::Append(std::string step)
{
    Step.push_back(step);
}
std::vector<std::string> StepLogger::CopyStep()
{
    return Step;
}
void StepLogger::Append(std::string Text, std::string latex, int level)
{
    std::string finalString = "";
    finalString += "\\text{";
    for(int i = 0; i < level; i++)
    {
        finalString +="   ";
    }
    if(level == 1)  {
        finalString += "- Step "+ std::to_string(counter) + ": "+ Text + "}";
        counter++;
    }else finalString +=  "- "+ Text + "}";
    finalString += latex;
    finalString += "\\\\";
    Step.push_back(finalString);
}