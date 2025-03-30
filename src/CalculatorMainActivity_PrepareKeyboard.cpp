#include <wx/wx.h>
#include <wx/timer.h>
#include "../scr/CalculatorMainActivity.hpp"
#include <memory>
#include "../scr/Button.hpp"
#include "../scr/GreenButton.hpp"
#include "../scr/BlackButton.hpp"
#include "../scr/OperationButton.hpp"
#include "../scr/SpecialButton.hpp"
wxBitmap prepareBitMap(std::string path)
{
    wxImage img(path.c_str());
    img.Rescale(100,30);
    return wxBitmap(img);
}
void CalculatorMainActivity::PrepareKeyboard()
{
    wxBitmap sin_ = prepareBitMap("./image/sin.png");
    wxBitmap cos_ = prepareBitMap("./image/cos.png");
    wxBitmap tan_ = prepareBitMap("./image/tan.png");
    wxBitmap cot_ = prepareBitMap("./image/cot.png");
    wxBitmap sec_ = prepareBitMap("./image/sec.png");
    wxBitmap csc_ = prepareBitMap("./image/csc.png");
    wxBitmap li_ = prepareBitMap("./image/li.png");
    wxBitmap ci_ = prepareBitMap("./image/ci.png");
    wxBitmap si_ = prepareBitMap("./image/si.png");
    wxBitmap squared_ = prepareBitMap("./image/squared.png");
    wxBitmap log10_ = prepareBitMap("./image/log10.png");
    wxBitmap ln_ = prepareBitMap("./image/ln.png");
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1000, "0", wxPoint(0, 480), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1001, "1", wxPoint(0, 450), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1002, "2", wxPoint(100, 450), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1003, "3", wxPoint(200, 450), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1004, "4", wxPoint(0, 420), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1005, "5", wxPoint(100, 420), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1006, "6", wxPoint(200, 420), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1007, "7", wxPoint(0, 390), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1008, "8", wxPoint(100, 390), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1009, "9", wxPoint(200, 390), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1010, ".", wxPoint(100, 480), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1011, "10^x", wxPoint(200, 480), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1012, "STO", wxPoint(0, 360), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1013, "VAR", wxPoint(100, 360), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1014, "S <-> D", wxPoint(200, 360), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1015, "(", wxPoint(0, 330), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1016, ")", wxPoint(100, 330), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1017, "dms", wxPoint(200, 330), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1018, "frac", wxPoint(0, 300), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1019, "sqrt", wxPoint(100, 300), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1020, "cubicroot", wxPoint(200, 300), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1021, "", wxPoint(0, 270), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(squared_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1022, "x^3", wxPoint(100, 270), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1023, "x^n", wxPoint(200, 270), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1024, "", wxPoint(0, 240), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(sin_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1025, "", wxPoint(100, 240), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(cos_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1026, "", wxPoint(200, 240), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(tan_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1027, "opt", wxPoint(0, 210), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1028, "shift", wxPoint(100, 210), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1029, "alpha", wxPoint(200, 210), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1030, "", wxPoint(300, 240), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(cot_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1031, "", wxPoint(400, 240), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(sec_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1032, "", wxPoint(500, 240), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(csc_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1033, "", wxPoint(300, 270), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(ln_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1034, "log10", wxPoint(400, 270), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(log10_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1035, "log", wxPoint(500, 270), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1036, "nthroot", wxPoint(300, 300), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1037, "x^-1", wxPoint(400, 300), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1038, "x!", wxPoint(500, 300), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1039, "sinh", wxPoint(300, 330), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1040, "cosh", wxPoint(400, 330), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1041, "tanh", wxPoint(500, 330), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1042, "coth", wxPoint(300, 360), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1043, "sech", wxPoint(400, 360), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1044, "csch", wxPoint(500, 360), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1045, "abs", wxPoint(300, 390), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1046, "round", wxPoint(400, 390), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1047, "floor", wxPoint(500, 390), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1048, "Up", wxPoint(400, 420), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1049, "Left", wxPoint(300, 450), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1050, "Right", wxPoint(500, 450), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1051, "Down", wxPoint(400, 480), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1052, ",", wxPoint(300, 420), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1053, "backspace", wxPoint(500, 420), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1054, "CALC", wxPoint(400, 450), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1055, "RandInt", wxPoint(300, 480), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1056, "Rand", wxPoint(500, 480), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<OperationButton>(this, 1057, "+", wxPoint(600, 480), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<OperationButton>(this, 1058, "-", wxPoint(700, 480), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<OperationButton>(this, 1059, "*", wxPoint(600, 450), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<OperationButton>(this, 1060, "/", wxPoint(700, 450), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1061, "e", wxPoint(300, 210), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1062, "e^x", wxPoint(400, 210), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1063, "pi", wxPoint(500, 210), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1064, "", wxPoint(600, 420), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(si_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1065, "", wxPoint(700, 420), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(ci_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1066, "Shi", wxPoint(600, 390), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1067, "Chi", wxPoint(700, 390), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1068, "", wxPoint(600, 360), wxSize(100, 30)));
    FirstPageButton.at(FirstPageButton.size()-1)->SetBitmap(li_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1069, "ProductLog", wxPoint(700, 360), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1070, "erf", wxPoint(600, 330), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1071, "erfc", wxPoint(700, 330), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1072, "erfi", wxPoint(600, 300), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1073, "gamma", wxPoint(700, 300), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1074, "zeta", wxPoint(600, 270), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1075, "EulerTotient", wxPoint(700, 270), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1076, "ProductLog(-1)", wxPoint(600, 240), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1077, "antiderivative", wxPoint(700, 240), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1078, "derivative", wxPoint(600, 210), wxSize(100, 30)));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1079, "MORE", wxPoint(700, 210), wxSize(100, 30)));
}