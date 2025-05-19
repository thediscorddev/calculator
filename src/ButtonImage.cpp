#include "../scr/ButtonImage.hpp"
ButtonImage::ButtonImage(std::shared_ptr<wxButton> button, wxBitmap image) : Button(button), Image(image)
{
    Button->SetBitmap(Image);
}
ButtonImage::ButtonImage(std::shared_ptr<wxButton> button) : Button(button)
{
}
ButtonImage::ButtonImage(std::shared_ptr<wxButton> button, std::string image) : Button(button)
{
    wxImage img(image.c_str(), wxBITMAP_TYPE_PNG); // Explicitly specify PNG format

    if (!img.IsOk())
    {
        wxLogError("Failed to load image from %s", image);
    }

    Image = wxBitmap(img);
    auto img2 = img;
    img2.Rescale(80, 24, wxIMAGE_QUALITY_HIGH);
    Button->SetBitmap( wxBitmap(img2));
}
void ButtonImage::SetBitmap(wxBitmap bitmap)
{
    Image = bitmap;
}
void ButtonImage::Hide()
{
    Button->Hide();
}
wxRect ButtonImage::GetRect()
{
    return Button->GetRect();
}
void ButtonImage::SetSize(wxRect rect)
{
    Button->SetSize(rect);
}
void ButtonImage::Rescale(int X, int Y)
{
    wxImage CopiedImg = Image.ConvertToImage();
    CopiedImg.Rescale(X, Y, wxIMAGE_QUALITY_HIGH);
    wxBitmap bitmap(CopiedImg);
    Button->SetBitmap(bitmap);
}
wxButton *  ButtonImage::get()
{
    return Button.get();
}
void ButtonImage::Show()
{
    Button->Show();
}