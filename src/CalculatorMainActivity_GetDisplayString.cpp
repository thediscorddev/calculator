#include "../scr/CalculatorMainActivity.hpp"
#include <string>
std::string CalculatorMainActivity::GetDisplayString(std::string CurrentString, int pos) {
    const int MaxLength = 20;
    const int StrLength = CurrentString.length();
    if (StrLength == 0) return CurrentString;

    int px = std::max(pos - MaxLength, 0);
    int py = std::min(pos + MaxLength, StrLength);

    std::string NewString = CurrentString.substr(px, py - px);

    if (px > 2)        NewString = "..." + NewString;
    else if (px == 2)  NewString = ".." + NewString;
    else if (px == 1)  NewString = "." + NewString;

    if (StrLength - py > 2)        NewString += "...";
    else if (StrLength - py == 2)  NewString += "..";
    else if (StrLength - py == 1)  NewString += ".";

    return NewString;
}
