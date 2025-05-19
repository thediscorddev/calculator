#pragma once
#include <vector>
#include "ButtonImage.hpp"
#include <memory>
class ButtonImageManager
{
private:
    std::vector<ButtonImage> container;

public:
    ButtonImageManager();
    void push_back(ButtonImage button);
    void push_back(std::shared_ptr<wxButton> button);
    ButtonImage at(int pos);
    std::vector<ButtonImage> & GetContainer();
    ButtonImage * operator[](std::size_t i);
    size_t size();
};