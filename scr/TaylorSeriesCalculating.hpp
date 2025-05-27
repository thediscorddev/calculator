#pragma once
#include <wx/wx.h>
#include <memory>
#include "Function_Composed.hpp"
#include <wx/webview.h> // For wxWebView
class TaylorSeriesCalculating : public wxFrame
{
private:
    wxWebView *webView = nullptr;
    std::shared_ptr<Function_Composed> TaylorSeriesFunc, OriginalFunc;
public:
    TaylorSeriesCalculating(wxWindow *parent, std::shared_ptr<Function_Composed> function, int terms, double centerX);
    void onButtonEvent(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};