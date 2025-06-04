#include "../scr/TaylorseriesHelper.hpp"
#include "../scr/TaylorseriesCalculating.hpp"
#include "../scr/FileManager.hpp"
#include "../scr/GreenButton.hpp"
#include "../scr/BlackButton.hpp"
#include "../scr/Button.hpp"
#include "../scr/OperationButton.hpp"
#include <memory>
#include <wx/webview.h> // For wxWebView
#include <wx/valnum.h>  // Required for wxIntegerValidator
#include <string>
TaylorseriesHelper::TaylorseriesHelper(wxWindow *parent, std::shared_ptr<Function_Composed> function)
    : wxFrame(parent, wxID_ANY, "Thein calculator: Taylor series helper", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    SetClientSize(800, 600);                             // 800 + padding, 80 + button height
    SetWindowStyle(GetWindowStyle() & ~wxRESIZE_BORDER); // Disable resizing (optional)
    SetSizeHints(800, 600, 800, 600);                    // minWidth, minHeight, maxWidth, maxHeight
    wxPanel *panel = new wxPanel(this);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    // Create the webView with fixed size
    wxWebView *webView = wxWebView::New(panel, wxID_ANY, "",
                                        wxDefaultPosition, wxSize(800, 160),
                                        wxWebViewBackendEdge, 0);
    sizer->Add(webView, 0, wxALIGN_CENTER | wxALL, 5); // Don't expand, keep fixed size

    // Create the button
    wxIntegerValidator<unsigned int> intValidator;
    wxFloatingPointValidator<double> doubleValidator(6);

    Button *findTaylor = new Button(panel, 10001, "Find the taylor series", wxDefaultPosition, wxDefaultSize);
    termBox = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 50), 0, intValidator);
    termBox->SetHint("Number of terms:");
    centerBox = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(100, 50), 0, doubleValidator);
    centerBox->SetHint("Centered x:");
    sizer->Add(termBox, 0, wxALIGN_CENTER | wxALL, 5);    // Below the web view
    sizer->Add(centerBox, 0, wxALIGN_CENTER | wxALL, 5);  // Below the web view
    sizer->Add(findTaylor, 0, wxALIGN_CENTER | wxALL, 5); // Below the web view
    func = function;
    panel->SetSizer(sizer);

    // Prepare your HTML content
    wxString html;
    html += "<!DOCTYPE html>\n<html>\n<head>\n";
    html += "<meta charset='utf-8'>\n";
    html += "<title>Thein calculator: Function displayer</title>\n";
    html += "<script>\n";
    html += "window.MathJax = {\n";
    html += "  tex: {\n";
    html += "    packages: ['base','color'],\n";
    html += "    inlineMath: [['$', '$'], ['\\\\(', '\\\\)']],\n";
    html += "    displayMath: [['$$', '$$'], ['\\\\[', '\\\\]']]\n";
    html += "  },\n";
    html += "  chtml: { scale: 2 }\n";
    html += "};\n";
    html += "</script>\n";
    html += "<script>";
    html += FileManager::MathJax;
    html += "</script>\n";
    html += "</head>\n<body>\n";
    html += "<p id='LatexExp'>$$\\begin{aligned}";
    html += "\\textbf{Input:} \\\\ " + function->toLatexString();
    html += "\\end{aligned}$$</p>\n</body>\n</html>";

    webView->SetPage(html, "");
}
void TaylorseriesHelper::onButtonEvent(wxCommandEvent &event)
{
    int id = event.GetId();
    if (id == 10001)
    {
        try
        {
            double CenterX = std::stod(centerBox->GetValue().ToStdString());
            int NumTerms = std::stoi(termBox->GetValue().ToStdString());
            if (NumTerms > 0)
            {
                auto *box = new TaylorSeriesCalculating(this, func, NumTerms, CenterX);
                box->Show();
            }
            else
                wxMessageBox("The entered value is invalid.", "Input Error", wxOK | wxICON_ERROR);
        }
        catch (...)
        {
            wxMessageBox("The entered value is invalid.", "Input Error", wxOK | wxICON_ERROR);
        }
    }
}
wxBEGIN_EVENT_TABLE(TaylorseriesHelper, wxFrame)
    EVT_BUTTON(wxID_ANY, TaylorseriesHelper::onButtonEvent) // Bind button event
    wxEND_EVENT_TABLE()