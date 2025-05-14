#include "../scr/StepLogger.hpp"
static std::vector<std::string> StepLogger::Step;
void StepLogger::Clear() {
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