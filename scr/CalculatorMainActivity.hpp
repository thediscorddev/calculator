#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include "Function.hpp"
#include "Function_Composed.hpp"
#include <functional>
struct FunctionReturn
{
    bool IsNull = true;
    std::shared_ptr<Function> func = nullptr;
};
class CalculatorMainActivity : public wxFrame {
public:
    CalculatorMainActivity(const wxString& title);
    static std::vector<std::string> CurrentInput;
    static     int CursorPosition; //default
    void SwitchButtonTheme(unsigned int id);
private:
    bool Shift = false;
    bool Alpha = false;
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
    void ShiftKeyboard();
    void AlphaKeyboard();
    Function_Composed CalculateDerivative(Function_Composed &function);
    Function_Composed CalculateDerivativeAndCreateNewOutLine(std::string OutlineType, std::shared_ptr<Function> Arg);
    std::string GetDisplayString(std::string CurrentString, int pos);
    std::string ToStringWithPrecision(double value, int precision = 16);
    std::vector<std::string> CalculateOperation(std::vector<std::string> PlannedOperation_);
    static std::map<std::string,double > constantList;
    static std::map<std::string, std::function<double(double)>> FunctionBatchOne;
    bool DisplayCursor = false;
    static std::map<int, std::string> ButtonClickInput;
    std::vector<std::shared_ptr<wxButton>> FirstPageButton, FirstPageButton_ShiftAffect, FirstPageButton_Shift;
    std::vector<wxRect> FirstPageButtonRect, FirstPageButtonShiftRect;
    std::vector<std::shared_ptr<wxButton>> SecondPageButton;
    FunctionReturn GetCurrentPosition_(std::shared_ptr<Function_Composed> func, int id, bool Create = true);
    std::shared_ptr<Function> GetCurrentPosition(std::shared_ptr<Function_Composed> func, int id, bool Create = true);
    wxTextCtrl* m_textCtrl;
    wxStaticText* result;
    wxButton* m_toggleButton; // Button for toggling
    wxTimer m_timer;

    wxDECLARE_EVENT_TABLE();
};