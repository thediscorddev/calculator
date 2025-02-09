#include "../scr/CalculatorMainActivity.hpp"
#include <sstream>
#include <string>
std::string CalculatorMainActivity::ToStringWithPrecision(double value, int precision)
{
    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << value;
    return out.str();
}