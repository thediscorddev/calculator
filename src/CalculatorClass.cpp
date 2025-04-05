#include <wx/wx.h>
#include "../scr/CalculatorClass.hpp"
#include "../scr/CalculatorMainActivity.hpp"
bool CalculatorClass::OnInit() {
    CalculatorMainActivity *frame = new CalculatorMainActivity("Thein calculator");
    frame->Show(true);
    return true;
}