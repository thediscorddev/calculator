#include <wx/wx.h>
#include "../scr/CalculatorMainActivity.hpp"
#include "../scr/ThemeChanger.hpp"
#include "../scr/Button.hpp"
#include "../scr/GreenButton.hpp"
#include "../scr/BlackButton.hpp"
#include "../scr/OperationButton.hpp"
#include "../scr/SpecialButton.hpp"
#include <memory>
#include <vector>
wxBEGIN_EVENT_TABLE(ThemeChanger, wxFrame)
    EVT_BUTTON(wxID_ANY, ThemeChanger::OnToggle)  // Add event handlers here
wxEND_EVENT_TABLE()
ThemeChanger::ThemeChanger(const wxString &title, CalculatorMainActivity *ptr)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 150)), activityptr(ptr)
{
    ButtonList.push_back(std::make_shared<BlackButton>(this, 1000, "Theme 1", wxPoint(0, 0), wxSize(300, 30)));
    ButtonList.push_back(std::make_shared<GreenButton>(this, 1001, "Theme 2", wxPoint(0, 30), wxSize(300, 30)));
    ButtonList.push_back(std::make_shared<SpecialButton>(this, 1002, "Theme 3", wxPoint(0, 60), wxSize(300, 30)));
    ButtonList.push_back(std::make_shared<OperationButton>(this, 1003, "Theme 4", wxPoint(0, 90), wxSize(300, 30)));
    ButtonList.push_back(std::make_shared<Button>(this, 1004, "Theme 5", wxPoint(0, 120), wxSize(300, 30)));
}
void ThemeChanger::OnToggle(wxCommandEvent &event)
{
    if (event.GetId() == 1000)
    {
        activityptr->SwitchButtonTheme(0);
    }
    else if (event.GetId() == 1001)
    {
        activityptr->SwitchButtonTheme(1);
    }
    else if (event.GetId() == 1002)
    {
        activityptr->SwitchButtonTheme(2);
    }
    else if (event.GetId() == 1003)
    {
        activityptr->SwitchButtonTheme(3);
    }
    else if (event.GetId() == 1004)
    {
        activityptr->SwitchButtonTheme(4);
    }
}