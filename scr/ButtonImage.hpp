#pragma once
#include <memory>
#include <wx/wx.h>
#include <string>
class ButtonImage
{
    private:
        std::shared_ptr<wxButton> Button;
        wxBitmap Image;
    public:
        ButtonImage(std::shared_ptr<wxButton> button, wxBitmap image); //origin image
        ButtonImage(std::shared_ptr<wxButton> button); //origin image
        ButtonImage(std::shared_ptr<wxButton> button, std::string image);
        void SetBitmap(wxBitmap bitmap);
        void Hide();
        void Show();
        wxRect GetRect();
        void SetSize(wxRect rect);
        void Rescale(int X, int Y);
        wxButton * get();
};