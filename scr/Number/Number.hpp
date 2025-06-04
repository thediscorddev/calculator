#pragma once
// THE NUMBER CLASS
#include <vector>
#include <string>
#include "Digit.hpp"
class Number
{
    protected:
        int decimalPlace = 0;
        std::vector<int> NumberArray;
    public:
        Number();
        void Append(Digit n);
        void setDecimal();
        double toDouble();
        float toFloat();
        int toInt();
        std::string toString();
        virtual Number operator+(Number const& b) = 0;
        Number operator-(Number const& b);
        Number operator*(Number const& b);
        Number operator/(Number const& b);
};