#include "../scr/CalculatorMainActivity.hpp"
#include <TMATH/t_math.hpp>
#include <string>
#include <functional>
#include <map>
std::map<std::string, double> CalculatorMainActivity::constantList;
std::map<std::string, std::function<double(double)>> CalculatorMainActivity::FunctionBatchOne;
void CalculatorMainActivity::PrepareFunction()
{
    constantList["pi"] = t_math::pi;
    constantList["e"] = t_math::e;
    FunctionBatchOne["sin("] = [](double x) {return t_math::sin(x);};
    FunctionBatchOne["cos("] = [](double x) {return t_math::cos(x);};
    FunctionBatchOne["tan("] = [](double x) {return t_math::tan(x);};
    FunctionBatchOne["cot("] = [](double x) {return t_math::cot(x);};
    FunctionBatchOne["sec("] = [](double x) {return t_math::sec(x);};
    FunctionBatchOne["csc("] = [](double x) {return t_math::csc(x);};
    FunctionBatchOne["exp("] = [](double x) {return t_math::exp(x);};
    FunctionBatchOne["sqrt("] = [](double x) {return t_math::sqrt(x);};
    FunctionBatchOne["ln("] = [](double x) {return t_math::ln(x);};
    FunctionBatchOne["log10("] = [](double x) {return t_math::log(x);};
    FunctionBatchOne["sinh("] = [](double x) {return t_math::sinh(x);};
    FunctionBatchOne["cosh("] = [](double x) {return t_math::cosh(x);};
    FunctionBatchOne["tanh("] = [](double x) {return t_math::tanh(x);};
    FunctionBatchOne["coth("] = [](double x) {return t_math::coth(x);};
    FunctionBatchOne["sech("] = [](double x) {return t_math::sech(x);};
    FunctionBatchOne["csch("] = [](double x) {return t_math::csch(x);};
    FunctionBatchOne["li("] = [](double x) {return t_math::li(x);};
    FunctionBatchOne["erf("] = [](double x) {return t_math::erf(x);};
    FunctionBatchOne["fac("] = [](double x) {return t_math::fac(x);};
    FunctionBatchOne["abs("] = [](double x) {return t_math::abs(x);};
    FunctionBatchOne["croot("] = [](double x) {return t_math::cubic_root(x);};
    FunctionBatchOne["ifrac("] = [](double x) {return 1/x;};
    FunctionBatchOne["floor("] = [](double x) {return t_math::floor(x);};
    FunctionBatchOne["ceil("] = [](double x) {return t_math::ceil(x);};
    FunctionBatchOne["squared("] = [](double x) {return t_math::pow(x,2);};
    FunctionBatchOne["cubed("] = [](double x) {return t_math::pow(x,3);};
    FunctionBatchOne["plogalter("] = [](double x) {return t_math::ProductLogAlternativeBranch(x);};
    FunctionBatchOne["zeta("] = [](double x) {return t_math::zeta(x);};
    FunctionBatchOne["eulertotient("] = [](double x) {return t_math::EulerTotient(t_math::floor(x));};
    FunctionBatchOne["erfi("] = [](double x) {return t_math::erfi(x);};
    FunctionBatchOne["erfc("] = [](double x) {return t_math::erfc(x);};
    FunctionBatchOne["gamma("] = [](double x) {return t_math::gamma(x);};
    FunctionBatchOne["productlog("] = [](double x) {return t_math::ProductLog(x);};
    FunctionBatchOne["shi("] = [](double x) {return t_math::shi(x);};
    FunctionBatchOne["si("] = [](double x) {return t_math::si(x);};
    FunctionBatchOne["chi("] = [](double x) {return t_math::shi(x);};
    FunctionBatchOne["ci("] = [](double x) {return t_math::ci(x);};
    FunctionBatchOne["pow(10,"] = [](double x) {return t_math::pow(10,x);};
    FunctionBatchOne["arcsin("] = [](double x) {return t_math::asin(x);};
    FunctionBatchOne["arccos("] = [](double x) {return t_math::acos(x);};
    FunctionBatchOne["arctan("] = [](double x) {return t_math::atan(x);};
    FunctionBatchOne["arcsec("] = [](double x) {return t_math::asec(x);};
    FunctionBatchOne["arccsc("] = [](double x) {return t_math::acsc(x);};
    FunctionBatchOne["arccot("] = [](double x) {return t_math::acot(x);};
    FunctionBatchOne["arcsinh("] = [](double x) {return t_math::asinh(x);};
    FunctionBatchOne["arccosh("] = [](double x) {return t_math::acosh(x);};
    FunctionBatchOne["arctanh("] = [](double x) {return t_math::atanh(x);};
    FunctionBatchOne["arcsech("] = [](double x) {return t_math::asech(x);};
    FunctionBatchOne["arccsch("] = [](double x) {return t_math::acsch(x);};
    FunctionBatchOne["arccoth("] = [](double x) {return t_math::acoth(x);};

}