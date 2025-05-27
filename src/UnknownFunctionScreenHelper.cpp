#include "../scr/UnknownFunctionScreenHelper.hpp"
#include "../scr/TaylorseriesHelper.hpp"
#include "../scr/FileManager.hpp"
#include "../scr/GreenButton.hpp"
#include "../scr/BlackButton.hpp"
#include "../scr/Button.hpp"
#include "../scr/OperationButton.hpp"
#include <memory>
#include <wx/webview.h> // For wxWebView
UnknownFunctionScreenHelper::UnknownFunctionScreenHelper(wxWindow *parent, std::shared_ptr<Function_Composed> function)
    : wxFrame(parent, wxID_ANY, "Thein calculator: Function menu", wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    SetClientSize(800, 600);                             // 800 + padding, 80 + button height
    SetWindowStyle(GetWindowStyle() & ~wxRESIZE_BORDER); // Disable resizing (optional)
    SetSizeHints(800, 600, 800, 600); // minWidth, minHeight, maxWidth, maxHeight
    wxPanel *panel = new wxPanel(this);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    // Create the webView with fixed size
    wxWebView *webView = wxWebView::New(panel, wxID_ANY, "",
                                        wxDefaultPosition, wxSize(800, 160),
                                        wxWebViewBackendEdge, 0);
    sizer->Add(webView, 0, wxALIGN_CENTER | wxALL, 5); // Don't expand, keep fixed size

    // Create the button
    Button *derivative = new Button(panel, 10001, "Find the derivative",wxDefaultPosition,wxDefaultSize);
    Button *taylorseries = new Button(panel, 10002, "Open taylor series helper",wxDefaultPosition,wxDefaultSize);
    Button *nthder = new Button(panel, 10003, "Find the nth derivative",wxDefaultPosition,wxDefaultSize);
    Button *graph = new Button(panel, 10004, "Graph the function",wxDefaultPosition,wxDefaultSize);
    Button *calc = new Button(panel, 10005, "Calculate it.",wxDefaultPosition,wxDefaultSize);
    sizer->Add(derivative, 0, wxALIGN_CENTER | wxALL, 5); // Below the web view
    sizer->Add(taylorseries, 0, wxALIGN_CENTER | wxALL, 5); // Below the web view
    sizer->Add(nthder, 0, wxALIGN_CENTER | wxALL, 5); // Below the web view
    sizer->Add(graph, 0, wxALIGN_CENTER | wxALL, 5); // Below the web view
    sizer->Add(calc, 0, wxALIGN_CENTER | wxALL, 5); // Below the web view
    func = function;
    panel->SetSizer(sizer);

    // Prepare your HTML content
    wxString html;
    html += "<!DOCTYPE html>\n<html>\n<head>\n";
    html += "<meta charset='utf-8'>\n";
    html += "<title>Thein calculator: Function with variable screen</title>\n";
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
    html += "\\textbf{The following function contains variables: } \\\\" + function->toLatexString() + "\\\\ \\textbf{What would you like to do?}";
    html += "$$</p>\n</body>\n</html>";

    webView->SetPage(html, "");
}
void UnknownFunctionScreenHelper::onButtonEvent(wxCommandEvent &event)
{
    int id = event.GetId();
    if(id == 10001)
    {

    }else if(id == 10002)
    {
        auto * Box = new TaylorseriesHelper(this,func);
        Box->Show();
    }else if(id == 10003)
    {

    }else if(id == 10004)
    {

    }else if(id == 10005)
    {

    }
}
wxBEGIN_EVENT_TABLE(UnknownFunctionScreenHelper, wxFrame)
EVT_BUTTON(wxID_ANY, UnknownFunctionScreenHelper::onButtonEvent) // Bind button event
wxEND_EVENT_TABLE()