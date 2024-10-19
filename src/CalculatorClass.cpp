#include <wx/wx.h>
#include "../scr/CalculatorClass.hpp"
#include "../scr/CalculatorMainActivity.hpp"
bool CalculatorClass::OnInit() {
    CalculatorMainActivity *frame = new CalculatorMainActivity("Calculator");
    frame->Show(true);
    return true;
}