#pragma once
// THE NUMBER CLASS
#include <vector>
#include <string>
class Number
{
    private:
        int decimalPlace = 0;
        std::vector<int> NumberArray;
    public:
        Number();
        void Append(int n);
        void setDecimal();
        double toDouble();
        float toFloat();
        int toInt();
        std::string toString();
        Number operator+(Number const& b);
        Number operator-(Number const& b);
        Number operator*(Number const& b);
        Number operator/(Number const& b);
};