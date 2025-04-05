#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include "Function_Composed.hpp"
#include <functional>
class CalculatorMainActivity : public wxFrame {
public:
    CalculatorMainActivity(const wxString& title);
    static std::vector<std::string> CurrentInput;
    static     int CursorPosition; //default
    void SwitchButtonTheme(unsigned int id);
private:
    void OnTimer(wxTimerEvent& event);
    void UpdateTime();
    void OnToggle(wxCommandEvent& event); // Handler for button toggle
    void PrepareKeyboard();
    void HandleClick();
    void UpdateContent();
    void UpdateContentWithCursor();
    double Calculate(int index = 1);
    void PrepareFunction();
    void OnResize(wxSizeEvent& event);
    static unsigned int theme; //default theme
    Function_Composed CalculateDerivative(Function_Composed &function);
    Function_Composed CalculateDerivativeAndCreateNewOutLine(std::string OutlineType, std::shared_ptr<Function> Arg);
    std::string GetDisplayString(std::string CurrentString, int pos);
    std::string ToStringWithPrecision(double value, int precision = 16);
    std::vector<std::string> CalculateOperation(std::vector<std::string> PlannedOperation_);
    static std::map<std::string,double > constantList;
    static std::map<std::string, std::function<double(double)>> FunctionBatchOne;
    bool DisplayCursor = false;
    static std::map<int, std::string> ButtonClickInput;
    std::vector<std::shared_ptr<wxButton>> FirstPageButton;
    std::vector<std::shared_ptr<wxButton>> FirstPageButton_Shift;
    std::vector<wxRect> FirstPageButtonRect;
    std::vector<std::shared_ptr<wxButton>> SecondPageButton;
    wxTextCtrl* m_textCtrl;
    wxStaticText* result;
    wxButton* m_toggleButton; // Button for toggling
    wxTimer m_timer;

    wxDECLARE_EVENT_TABLE();
};