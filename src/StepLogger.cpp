#include "../scr/StepLogger.hpp"
#include "../scr/CalculatorMainActivity.hpp"
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
    for(int i = 0; i < level; i++)
    {
        finalString +="\\quad ";
    }
    finalString += "\\textbf{";
    if(level == 1)  {
        finalString += "- "+ std::to_string(counter) + ": "+ Text + "}";
        counter++;
    }else finalString +=  "- "+ Text + "}";
    finalString += "\\textcolor{blue}{" + latex + "}";
    finalString += "\\\\";
    Step.push_back(finalString);
}
void StepLogger::Append(std::string Text1, std::string Text2, std::string latex, int level)
{
    if(CalculatorMainActivity::lang == 1)
    {
        Append(Text1,latex,level);
    }else if(CalculatorMainActivity::lang == 2)
    {
        Append(Text2,latex,level);
    }
}