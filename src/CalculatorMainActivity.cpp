#include <wx/wx.h>
#include <wx/timer.h>
#include "../scr/CalculatorMainActivity.hpp"
#include "../scr/CustomTextCtrl.hpp"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "../scr/Button.hpp"
#include "../scr/GreenButton.hpp"
#include "../scr/BlackButton.hpp"
#include "../scr/OperationButton.hpp"
#include "../scr/SpecialButton.hpp"
#include "../scr/ThemeChanger.hpp"
#include "../scr/ResultDisplay.hpp"
#include "../scr/FileManager.hpp"
#include "../scr/Derivative.hpp"
unsigned int CalculatorMainActivity::theme = 0; // Initialize here
std::map<int, std::string> CalculatorMainActivity::ButtonClickInput;
std::vector<std::string> CalculatorMainActivity::CurrentInput;
int CalculatorMainActivity::lang = 1;
int CalculatorMainActivity::CursorPosition = 1; // default =

// Then in your constructor:
CalculatorMainActivity::CalculatorMainActivity(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(880, 600)),
      m_timer(this)
{
    FileManager::PrepareFile();
#if wxUSE_WEBVIEW_EDGE
    std::cout << "Edge backend enabled at compile time\n";
#else
    std::cout << "Edge backend disabled at compile time\n";
#endif
    SetEnvironmentVariableW(L"WEBVIEW2_BROWSER_EXECUTABLE_FOLDER", L".\\WebView2Runtime");
    wxImage::AddHandler(new wxPNGHandler());
    webView = wxWebView::New(this, wxID_ANY, "",
                             wxPoint(0, 0), wxSize(800, 200), wxWebViewBackendEdge, 0);
    wxString html;
    html += "<!DOCTYPE html>\n<html>\n<head>\n";
    html += "<meta charset='utf-8'>\n";
    html += "<title>Thein calculator: Derivative result</title>\n";
    html += "<script>\n";
    html += "window.MathJax = {\n";
    html += "  tex: {\n";
    html += "    packages: ['base','color'],\n";
    html += "    inlineMath: [['$', '$'], ['\\\\(', '\\\\)']],\n";
    html += "    displayMath: [['$$', '$$'], ['\\\\[', '\\\\]']]\n";
    html += "  },\n";
    html += "  chtml: { scale: 1 }\n";
    html += "};\n";
    html += "</script>\n";
    html += "<script type=\"text/javascript\">";
    html += "if (window.MathJax) {";
    html += "MathJax.Hub.Queue([\"Typeset\", MathJax.Hub]);";
    html += "}";
    html += "</script>";
    html += "<script>";
    html += FileManager::MathJax;
    html += "</script>";
    // html += "<script src=\"" + mathjaxPath + "\"></script>\n"; // e.g., js/mathjax/es5/tex-chtml.js
    // html += "<script src=\"https://cdn.jsdelivr.net/npm/mathjax@2.7.9/MathJax.js?config=TeX-AMS_HTML\"></script>\n";
    html += "</head>\n<body>\n";
    //html += "<h1>Result</h1>\n";
    html += "<p id = 'LatexExp'>$$";
    html += "\textcolor{blue}{\\textbf{This is an example coloring}}"; // This should be your long LaTeX expression
    html += "$$</p>";

    html += "</body>\n</html>\n";
    // webView->SetPage("<html><body><h1>Edge backend test</h1><p>Hello, world</p></body></html>", "");
    webView->SetPage(html, "");
    m_textCtrl = new CustomTextCtrl(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 200));
    m_textCtrl->SetSize(m_textCtrl->GetSize().GetWidth(), m_textCtrl->GetSize().GetHeight());
    m_textCtrl->SetScrollPos(wxHORIZONTAL, 0);
    m_textCtrl->SetScrollbar(wxHORIZONTAL, 0, 0, 0);
    wxInitAllImageHandlers();
    // Ensure client size is exact
    SetClientSize(wxSize(800, 510));

    PrepareFunction();
    // Create the text box at (0,0) with size 800x200
    // result = new TransparentStaticText(this, wxID_ANY, wxT(""), wxPoint(500, 210), wxSize(200, 100)); //
    ((CustomTextCtrl *)m_textCtrl)->SetOverlayText("");

    wxFont font(30, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Courier New");

    // Set fonts and colors
    m_textCtrl->SetBackgroundColour(wxColour(196, 196, 196)); // Light gray background
    m_textCtrl->SetForegroundColour(wxColour(0, 0, 0));       // Black text
    m_textCtrl->SetFont(font);

    // result->SetFont(font);
    // result->SetForegroundColour(wxColour(0, 0, 0)); // Black text

    // Other init
    PrepareKeyboard();
    HandleClick();
    derivative::prepareDerivativeTable();
    m_timer.Start(500); // Start timer
    m_textCtrl->Hide();
    m_textCtrl->Enable(false);
    this->Layout();
}

void CalculatorMainActivity::UpdateContent()
{
    if (DisplayCursor == true)
        UpdateContentWithCursor();
    else
    {
        int Pos = 0;
        int i = 0;
        std::string CurrentDisplayedText = "";
        for (const auto &a : CurrentInput)
        {
            if (i <= CursorPosition)
            {
                Pos += a.length();
                i++;
            }
            CurrentDisplayedText += a;
        }
        ((CustomTextCtrl *)m_textCtrl)->SetSecondOverlayText(GetDisplayString(CurrentDisplayedText, Pos));
        ((CustomTextCtrl *)m_textCtrl)->SetOverlayText("");
    }
}
void CalculatorMainActivity::UpdateContentWithCursor()
{
    DisplayCursor = (DisplayCursor != false);
    ((CustomTextCtrl *)m_textCtrl)->DisplayCursor(DisplayCursor, CursorPosition, CurrentInput);
}

void CalculatorMainActivity::OnTimer(wxTimerEvent &event)
{
}

void CalculatorMainActivity::UpdateTime()
{
    wxDateTime now = wxDateTime::Now();
    // m_textCtrl->SetSecondOverlayText(now.Format("%H:%M:%S")); // Update the text box with the current time
}
void CalculatorMainActivity::SwitchButtonTheme(unsigned int id)
{
    for (auto &a : FirstPageButton.GetContainer())
    {
        if (dynamic_cast<BlackButton *>(a.get()))
        {
            dynamic_cast<BlackButton *>(a.get())->ChangeTheme(id);
        }
        else if (dynamic_cast<GreenButton *>(a.get()))
        {
            dynamic_cast<GreenButton *>(a.get())->ChangeTheme(id);
        }
        else if (dynamic_cast<SpecialButton *>(a.get()))
        {
            dynamic_cast<SpecialButton *>(a.get())->ChangeTheme(id);
        }
        else if (dynamic_cast<OperationButton *>(a.get()))
        {
            dynamic_cast<OperationButton *>(a.get())->ChangeTheme(id);
        }
        else if (dynamic_cast<Button *>(a.get()))
        {
            dynamic_cast<Button *>(a.get())->ChangeTheme(id);
        }
    }
    for (auto &a : FirstPageButton_Shift.GetContainer())
    {
        if (dynamic_cast<BlackButton *>(a.get()))
        {
            dynamic_cast<BlackButton *>(a.get())->ChangeTheme(id);
        }
        else if (dynamic_cast<GreenButton *>(a.get()))
        {
            dynamic_cast<GreenButton *>(a.get())->ChangeTheme(id);
        }
        else if (dynamic_cast<SpecialButton *>(a.get()))
        {
            dynamic_cast<SpecialButton *>(a.get())->ChangeTheme(id);
        }
        else if (dynamic_cast<OperationButton *>(a.get()))
        {
            dynamic_cast<OperationButton *>(a.get())->ChangeTheme(id);
        }
        else if (dynamic_cast<Button *>(a.get()))
        {
            dynamic_cast<Button *>(a.get())->ChangeTheme(id);
        }
    }
    this->Layout();
}
void CalculatorMainActivity::OnToggle(wxCommandEvent &event)
{
    bool SpecialFunction = false;
    // Toggle the enabled state of the text box
    // bool isEnabled = m_textCtrl->IsEnabled();
    // m_textCtrl->Enable(!isEnabled); // Toggle the enabled state
    // m_toggleButton->SetLabel(isEnabled ? "Enable Text Box" : "Disable Text Box");
    int specialfunc[] = {1012, 1013, 1014, 1027, 1028, 1029, 1048, 1049, 1050, 1051, 1053, 1054, 1079};
    for (const auto &a : specialfunc)
    {
        if (event.GetId() == a)
        {
            SpecialFunction = true;
            break;
        }
    }
    if (SpecialFunction == false && ButtonClickInput.find(event.GetId()) != ButtonClickInput.end())
    {
        CurrentInput.insert(CurrentInput.begin() + (CursorPosition - 1), ButtonClickInput[event.GetId()]);
        CursorPosition++;
        UpdateContent();
    }
    if (SpecialFunction == true)
    {
        int id_ = event.GetId();
        if (id_ == 1053)
        {
            if (CurrentInput.size() != 0)
            {
                CurrentInput.pop_back();
                CursorPosition--;
                UpdateContent();
            }
        }
        else if (id_ == 1049)
        {
            if (CursorPosition - 1 > 0)
                CursorPosition--;
            ((CustomTextCtrl *)m_textCtrl)->Refreshs();
        }
        else if (id_ == 1050)
        {
            if (CursorPosition - 1 < CurrentInput.size())
                CursorPosition++;
            ((CustomTextCtrl *)m_textCtrl)->Refreshs();
        }
        else if (id_ == 1054)
        {
            try
            {
                // result->SetLabel(std::to_string(Calculate()));
                double result = Calculate(); // Assuming Calculate returns double

                // Option 1: wxString::Format (recommended)
                ((CustomTextCtrl *)m_textCtrl)->SetOverlayText(wxString::Format("%.10g", result)); // Format as string
                // ResultDisplay *frame = new ResultDisplay("Result",NULL);
            }
            catch (std::exception &e)
            {
                // result->SetLabel(e.what());
                ResultDisplay *frame = new ResultDisplay("Error", e.what());
            }
        }
        else if (id_ == 1027)
        {
            ThemeChanger *frame = new ThemeChanger("Change button theme", this);
            frame->Show(true);
        }
        else if (id_ == 1028)
        {
            Shift = (Shift == true) ? false : true;
            Alpha = false;
            ShiftKeyboard();
        }
        else if (id_ == 1029)
        {
            Alpha = (Alpha == true) ? false : true;
            Shift = false;
            AlphaKeyboard();
        }
    }
}
void CalculatorMainActivity::OnPageReady(wxWebViewEvent& event)
{
    IsRendererReady = true;
}