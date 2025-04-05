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
        wxImage img = FirstPageButton[i]->GetBitmap().ConvertToImage();                                               // Convert wxBitmap to wxImage
        img.Rescale(static_cast<int>(mX * elRect.width), static_cast<int>(mY * elRect.height), wxIMAGE_QUALITY_HIGH); // Resize bitmap
        wxBitmap resizedBitmap(img);                                                                                  // Convert back to wxBitmap
        FirstPageButton[i]->SetBitmap(resizedBitmap);
    }
    if(m_textCtrl != nullptr)
    {
        m_textCtrl->SetSize(static_cast<int>(mX * 800), static_cast<int>(mY * 200));
    }
    event.Skip(); // Propagate the event
}
