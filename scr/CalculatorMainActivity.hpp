#include <wx/wx.h>
#include <wx/timer.h>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <functional>
class CalculatorMainActivity : public wxFrame {
public:
    CalculatorMainActivity(const wxString& title);

private:
    void OnTimer(wxTimerEvent& event);
    void UpdateTime();
    void OnToggle(wxCommandEvent& event); // Handler for button toggle
    void PrepareKeyboard();
    void HandleClick();
    void UpdateContent();
    void UpdateContentWithCursor();
    void Parse();
    void PrepareFunction();

    static std::map<std::string, std::function<double(double)>> FunctionBatchOne;
    int CursorPosition = 1; //default
    bool DisplayCursor = false;
    static std::map<int, std::string> ButtonClickInput;
    static std::vector<std::string> CurrentInput;
    std::vector<std::shared_ptr<wxButton>> FirstPageButton;
    std::vector<std::shared_ptr<wxButton>> SecondPageButton;
    wxTextCtrl* m_textCtrl;
    wxButton* m_toggleButton; // Button for toggling
    wxTimer m_timer;

    wxDECLARE_EVENT_TABLE();
};