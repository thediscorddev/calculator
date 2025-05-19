#include "../scr/CalculatorMainActivity.hpp"
#include <iostream>
void CalculatorMainActivity::OnResize(wxSizeEvent &event)
{
    wxSize size = GetClientSize(); // Get updated window size
    if (size.y == 0)
    {
        std::cout << "Invalid window size, size.y is 0!" << std::endl;
        event.Skip();
        return;
    }

    double mX = size.x / 800.0; // Scale factor for width
    double mY = size.y / 510.0; // Scale factor for height

    for (int i = 0; i < FirstPageButton.size(); i++)
    {
        wxRect &elRect = FirstPageButtonRect.at(i);

        FirstPageButton[i]->SetSize(wxRect(static_cast<int>(mX * elRect.x),
                                           static_cast<int>(mY * elRect.y),
                                           static_cast<int>(mX * elRect.width),
                                           static_cast<int>(mY * elRect.height)));

        // Resize bitmap
        FirstPageButton[i]->Rescale(static_cast<int>(mX * elRect.width * 0.8), static_cast<int>(mY * elRect.height * 0.8));
    }
    for (int i = 0; i < FirstPageButton_Shift.size(); i++)
    {
        wxRect &elRect = FirstPageButtonShiftRect.at(i);

        FirstPageButton_Shift[i]->SetSize(wxRect(static_cast<int>(mX * elRect.x),
                                                 static_cast<int>(mY * elRect.y),
                                                 static_cast<int>(mX * elRect.width),
                                                 static_cast<int>(mY * elRect.height)));

        FirstPageButton_Shift[i]->Rescale(static_cast<int>(mX * elRect.width * 0.8), static_cast<int>(mY * elRect.height * 0.8));
    }
    if (m_textCtrl != nullptr)
    {
        m_textCtrl->SetSize(static_cast<int>(mX * 800), static_cast<int>(mY * 200));
    }
    if (webView != nullptr)
    {
        webView->SetSize(wxSize(static_cast<int>(mX * 800), static_cast<int>(mY * 200)));
        wxString script = "document.body.style.transformOrigin = \"0 0\";";
        script+="document.body.style.transform = \"scale("+std::to_string(static_cast<float>(mX))+","+ std::to_string(static_cast<float>(mY))+")\";";
        if(IsRendererReady) webView->RunScript(script);
    }
    event.Skip(); // Propagate the event
}
