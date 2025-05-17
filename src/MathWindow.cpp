#include "../scr/MathWindow.hpp"
#include "../scr/StepLogger.hpp"
#include <wx/webview.h>  // For wxWebView
#include <wx/stdpaths.h> // For wxStandardPaths
#include <wx/filename.h> // For wxFileName

MathWindow::MathWindow(wxWindow *parent)
    : wxFrame(parent, wxID_ANY, "Thein calculator: Derivative result", wxDefaultPosition, wxSize(800, 600))
{
    wxWebView *webView = wxWebView::New(this, wxID_ANY);
    std::string Step = "";
    for (auto str : StepLogger::CopyStep())
    {
        Step += str;
    }
    // Get the absolute path to MathJax
    wxString exePath = wxStandardPaths::Get().GetExecutablePath();
    wxFileName exeFile(exePath);
    wxString baseDir = exeFile.GetPath(); // e.g., /home/user/myapp or C:\Users\...

    wxString mathjaxPath = "file://" + baseDir + "/js/mathjax/es5/tex-mml-chtml.js";
    wxString latexExpr(Step);
    wxString html;
    html += "<!DOCTYPE html>\n<html>\n<head>\n";
    html += "<meta charset='utf-8'>\n";
    html += "<title>Thein calculator: Derivative result</title>\n";
    html += "<script>\n";
    html += "window.MathJax = {\n";
    html += "  tex: {\n";
    html += "    inlineMath: [['$', '$'], ['\\\\(', '\\\\)']],\n";
    html += "    displayMath: [['$$', '$$'], ['\\\\[', '\\\\]']]\n";
    html += "  },\n";
    html += "  chtml: { scale: 1 }\n";
    html += "};\n";
    html += "</script>\n";
    //html += "<script src=\"" + mathjaxPath + "\"></script>\n"; // e.g., js/mathjax/es5/tex-chtml.js
    html += "<script src=\"https://cdn.jsdelivr.net/npm/mathjax@2.7.9/MathJax.js?config=TeX-AMS_HTML\"></script>\n";
    html += "</head>\n<body>\n";
    html += "<h1>Result</h1>\n";
    html += "<p>$$\\[";
    html += latexExpr; // This should be your long LaTeX expression
    html += "\\]$$</p>";

    html += "</body>\n</html>\n";

    webView->SetPage(html, "");
}