#include "../scr/MathWindow.hpp"
#include "../scr/StepLogger.hpp"
#include "../scr/FileManager.hpp"
#include <wx/webview.h>  // For wxWebView
#include <wx/stdpaths.h> // For wxStandardPaths
#include <wx/filename.h> // For wxFileName
#include <fstream>
#include <iostream>

MathWindow::MathWindow(wxWindow *parent)
    : wxFrame(parent, wxID_ANY, "Thein calculator: Derivative result", wxDefaultPosition, wxSize(800, 600))
{
    wxWebView *webView = wxWebView::New(this, wxID_ANY, wxWebViewDefaultURLStr, wxDefaultPosition, wxDefaultSize, wxWebViewBackendEdge, 0, wxWebViewNameStr);
    std::string Step = "";
    for (auto str : StepLogger::CopyStep())
    {
        Step += str;
    }
    // Get the absolute path to MathJax
    wxString exePath = wxStandardPaths::Get().GetExecutablePath();
    wxFileName exeFile(exePath);
    wxString baseDir = exeFile.GetPath(); // e.g., /home/user/myapp or C:\Users\...
    wxString mathjaxPath = "file:///" + baseDir;
    wxString latexExpr = wxString::FromUTF8(Step);
    wxString html;
    html += "<!DOCTYPE html>\n<html>\n<head>\n";
    html += "<meta charset='utf-8'>\n";
    html += "<title>Thein calculator: Derivative result</title>\n";
    html += "<script>\n";
    html += "window.MathJax = {\n";
    html += "  tex: {\n";
    //html += "    packages: ['base','color'],\n";
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
    html += "<p>$$";
    html += latexExpr; // This should be your long LaTeX expression
    html += "$$</p>";

    html += "</body>\n</html>\n";
    // webView->SetPage("<html><body><h1>Edge backend test</h1><p>Hello, world</p></body></html>", "");
    webView->SetPage(html, "file:///" + baseDir + "/");
}