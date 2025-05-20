#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include <memory>
#include <vector>
#include <wx/webview.h>  // For wxWebView
#include <string>
#include <map>
#include "Function.hpp"
#include "ButtonImageManager.hpp"
#include "Function_Composed.hpp"
#include "Function_Variable.hpp"
#include <functional>
struct FunctionReturn
{
    bool IsNull = true;
    std::shared_ptr<Function> func = nullptr;
};
class CalculatorMainActivity : public wxFrame {
public:
    static int lang; //for push step, 1 is eng, 2 is vn
    CalculatorMainActivity(const wxString& title);
    static std::vector<std::string> CurrentInput;
    static     int CursorPosition; //default
    void SwitchButtonTheme(unsigned int id);
private:
    bool IsRendererReady = false;
    bool Shift = false;
    bool Alpha = false;
    void OnPageReady(wxWebViewEvent& event);
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
    std::shared_ptr<Function_Composed> Parse(int index, bool warning = true);
    Function_Composed CalculateDerivative(Function_Composed &function);
    Function_Composed CalculateDerivativeAndCreateNewOutLine(std::string OutlineType, std::shared_ptr<Function> Arg);
    std::string GetDisplayString(std::string CurrentString, int pos);
    std::string ToStringWithPrecision(double value, int precision = 16);
    std::vector<std::string> CalculateOperation(std::vector<std::string> PlannedOperation_);
    static std::map<std::string,double > constantList;
    static std::map<std::string, std::function<double(double)>> FunctionBatchOne;
    bool DisplayCursor = false;
    static std::map<int, std::string> ButtonClickInput;
    ButtonImageManager FirstPageButton, FirstPageButton_ShiftAffect, FirstPageButton_Shift;
    std::vector<wxRect> FirstPageButtonRect, FirstPageButtonShiftRect;
    std::vector<std::shared_ptr<wxButton>> SecondPageButton;
    FunctionReturn GetCurrentPosition_(std::shared_ptr<Function_Composed> func, int id, bool Create = true);
    std::shared_ptr<Function> GetCurrentPosition(std::shared_ptr<Function_Composed> func, int id, bool Create = true);
    wxTextCtrl* m_textCtrl=nullptr;
    wxStaticText* result=nullptr;
    wxButton* m_toggleButton=nullptr; // Button for toggling
    wxTimer m_timer;
    wxWebView* webView=nullptr;

    wxDECLARE_EVENT_TABLE();
};