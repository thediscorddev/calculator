#include "../scr/ButtonImageManager.hpp"
ButtonImageManager::ButtonImageManager()
{
}
void ButtonImageManager::push_back(std::shared_ptr<wxButton> button)
{
    ButtonImage Button(button);
    container.push_back(Button);
}
void ButtonImageManager::push_back(ButtonImage button)
{
    container.push_back(button);
}
ButtonImage ButtonImageManager::at(int pos)
{
    return container.at(pos);
}
std::vector<ButtonImage> &ButtonImageManager::GetContainer()
{
    return container;
}
ButtonImage *ButtonImageManager::operator[](std::size_t i)
{
    if (i >= container.size())
    {
        throw std::out_of_range("Index out of range");
    }
    return &container[i]; // returned by value, ref count incremented
}
size_t ButtonImageManager::size()
{
    return container.size();
}