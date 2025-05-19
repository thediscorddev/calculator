#include <wx/wx.h>
#include <wx/timer.h>
#include "../scr/CalculatorMainActivity.hpp"
#include <memory>
#include "../scr/Button.hpp"
#include "../scr/GreenButton.hpp"
#include "../scr/BlackButton.hpp"
#include "../scr/OperationButton.hpp"
#include "../scr/SpecialButton.hpp"
#include <string>
#include <iostream>
void CalculatorMainActivity::ShiftKeyboard()
{
    if(Shift == true)
    {
        for(auto & a: FirstPageButton_ShiftAffect.GetContainer())
        {
            a.Hide();
        }
        for(auto & a: FirstPageButton_Shift.GetContainer())
        {
            a.Show();
        }
    }else {
        for(auto & a: FirstPageButton_ShiftAffect.GetContainer())
        {
            a.Show();
        }
        for(auto & a: FirstPageButton_Shift.GetContainer())
        {
            a.Hide();
        }
    }
    this->Layout();
}
void CalculatorMainActivity::AlphaKeyboard()
{
    if(Shift == true)
    {
        for(auto & a: FirstPageButton_ShiftAffect.GetContainer())
        {
            a.Hide();
        }
        for(auto & a: FirstPageButton_Shift.GetContainer())
        {
            a.Show();
        }
    }else {
        for(auto & a: FirstPageButton_ShiftAffect.GetContainer())
        {
            a.Show();
        }
        for(auto & a: FirstPageButton_Shift.GetContainer())
        {
            a.Hide();
        }
    }
}