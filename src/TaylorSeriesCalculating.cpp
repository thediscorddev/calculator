#include "../scr/TaylorSeriesCalculating.hpp"
#include "../scr/TaylorSeries.hpp"
#include "../scr/FileManager.hpp"
#include "../scr/GreenButton.hpp"
#include "../scr/BlackButton.hpp"
#include "../scr/Button.hpp"
#include "../scr/OperationButton.hpp"
#include <memory>
#include <wx/webview.h> // For wxWebView
#include <wx/valnum.h>  // Required for wxIntegerValidator
#include <string>
#include <wx/clipbrd.h>
TaylorSeriesCalculating::TaylorSeriesCalculating(wxWindow *parent, std::shared_ptr<Function_Composed> function, int terms, double centerX)
    : wxFrame(parent, wxID_ANY, "Thein calculator: Taylor series result", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
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
    OriginalFunc = function;
    TaylorSeriesFunc = TaylorSeries::GenerateTaylorSeries(OriginalFunc, centerX, terms);
    // Create the button

    Button *CopyEx = new Button(panel, 10001, "Copy original expression", wxDefaultPosition, wxDefaultSize);
    Button *CopyEx2 = new Button(panel, 10002, "Copy Taylor series expression", wxDefaultPosition, wxDefaultSize);
    sizer->Add(CopyEx, 0, wxALIGN_CENTER | wxALL, 5);  // Below the web view
    sizer->Add(CopyEx2, 0, wxALIGN_CENTER | wxALL, 5); // Below the web view

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
    html += "<p id='LatexExp'>$$";
    html += "\\textbf{Result: } \\\\" + TaylorSeriesFunc->toLatexString();
    html += "$$</p>\n</body>\n</html>";

    webView->SetPage(html, "");
}
void TaylorSeriesCalculating::onButtonEvent(wxCommandEvent &event)
{
    int id = event.GetId();
    if (id == 10001)
    {
        if (wxTheClipboard->Open())
        {
            wxTheClipboard->SetData(new wxTextDataObject(TaylorSeriesFunc->toLatexString()));
            wxTheClipboard->Close();
            wxMessageBox("Successfully copied expression to clipboard.", "Information", wxOK | wxICON_INFORMATION);
        }else wxMessageBox("Failed to copy expression to clipboard.", "Error", wxOK | wxICON_ERROR);
    }
    else if (id == 10002)
    {
        if (wxTheClipboard->Open())
        {
            wxTheClipboard->SetData(new wxTextDataObject(OriginalFunc->toLatexString()));
            wxTheClipboard->Close();
            wxMessageBox("Successfully copied expression to clipboard.", "Information", wxOK | wxICON_INFORMATION);
        }else wxMessageBox("Failed to copy expression to clipboard.", "Error", wxOK | wxICON_ERROR);
    }
}
wxBEGIN_EVENT_TABLE(TaylorSeriesCalculating, wxFrame)
    EVT_BUTTON(wxID_ANY, TaylorSeriesCalculating::onButtonEvent) // Bind button event
    wxEND_EVENT_TABLE()