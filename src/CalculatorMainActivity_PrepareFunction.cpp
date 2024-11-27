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
    FunctionBatchOne["exp("] = [](double x) {return t_math::exp(x);};
    FunctionBatchOne["sqrt("] = [](double x) {return t_math::sqrt(x);};
    FunctionBatchOne["ln("] = [](double x) {return t_math::ln(x);};
    FunctionBatchOne["log("] = [](double x) {return t_math::log(x);};
    FunctionBatchOne["sinh("] = [](double x) {return t_math::sinh(x);};
    FunctionBatchOne["cosh("] = [](double x) {return t_math::cosh(x);};
    FunctionBatchOne["tanh("] = [](double x) {return t_math::tanh(x);};
    FunctionBatchOne["coth("] = [](double x) {return t_math::coth(x);};
    FunctionBatchOne["sech("] = [](double x) {return t_math::sech(x);};
    FunctionBatchOne["csch("] = [](double x) {return t_math::csch(x);};
    FunctionBatchOne["li("] = [](double x) {return t_math::li(x);};
    FunctionBatchOne["erf("] = [](double x) {return t_math::erf(x);};
}