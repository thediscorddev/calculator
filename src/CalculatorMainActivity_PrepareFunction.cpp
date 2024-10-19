#include "../scr/CalculatorMainActivity.hpp"
#include <TMATH/t_math.hpp>
#include <string>
#include <functional>
#include <map>
std::map<std::string, std::function<double(double)>> CalculatorMainActivity::FunctionBatchOne;
void CalculatorMainActivity::PrepareFunction()
{
    FunctionBatchOne["sin("] = [](double x) {return t_math::sin(x);};
    FunctionBatchOne["cos("] = [](double x) {return t_math::cos(x);};
    FunctionBatchOne["tan("] = [](double x) {return t_math::tan(x);};
    FunctionBatchOne["cot("] = [](double x) {return t_math::cot(x);};
    FunctionBatchOne["sec("] = [](double x) {return t_math::sec(x);};
    FunctionBatchOne["csc("] = [](double x) {return t_math::csc(x);};
}