#include <wx/wx.h>
#include <wx/timer.h>
#include "scr/CalculatorClass.hpp"
#include "scr/CalculatorMainActivity.hpp"
#include "scr/CustomTextCtrl.hpp"
#include "scr/ThemeChanger.hpp"
wxBEGIN_EVENT_TABLE(CalculatorMainActivity, wxFrame)
EVT_TIMER(wxID_ANY, CalculatorMainActivity::OnTimer)
EVT_BUTTON(wxID_ANY, CalculatorMainActivity::OnToggle) // Bind button event
EVT_SIZE(CalculatorMainActivity::OnResize)
wxEND_EVENT_TABLE()
wxBEGIN_EVENT_TABLE(CustomTextCtrl, wxTextCtrl)
    EVT_PAINT(CustomTextCtrl::OnPaint)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(CalculatorClass);
