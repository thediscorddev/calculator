#include <wx/wx.h>
#include "../scr/ResultDisplay.hpp"
#include "../scr/LatexPanel.hpp"
wxBEGIN_EVENT_TABLE(ResultDisplay, wxFrame)
wxEND_EVENT_TABLE()
ResultDisplay::ResultDisplay(const wxString& title, Function_Composed * Result): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 190))
{
    new LatexPanel(this);
    this->Show(true);
}
ResultDisplay::ResultDisplay(const wxString& title, const wxString& Message): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 190))
{
    wxStaticText* staticText = new wxStaticText(this, wxID_ANY, Message, wxPoint(0, 0));
    staticText->SetFont(wxFont(28, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    this->Show(true);
}