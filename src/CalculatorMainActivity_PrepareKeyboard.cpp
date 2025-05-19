#include <wx/wx.h>
#include <wx/timer.h>
#include "../scr/CalculatorMainActivity.hpp"
#include <memory>
#include "../scr/Button.hpp"
#include "../scr/GreenButton.hpp"
#include "../scr/BlackButton.hpp"
#include "../scr/OperationButton.hpp"
#include "../scr/SpecialButton.hpp"
#include <string>
#include <iostream>
wxBitmap prepareBitMap(std::string path)
{
    wxImage img(path.c_str(), wxBITMAP_TYPE_PNG);  // Explicitly specify PNG format

    if (!img.IsOk()) {
        wxLogError("Failed to load image from %s", path);
        return wxBitmap();  // Return an invalid bitmap
    }


    img.Rescale(80, 24, wxIMAGE_QUALITY_HIGH);
    return wxBitmap(img);
}

void CalculatorMainActivity::PrepareKeyboard()
{
    wxBitmap sin_ = prepareBitMap("./image/sin.png");
    wxBitmap arcsin_ = prepareBitMap("./image/arcsin.png");
    wxBitmap arccos_ = prepareBitMap("./image/arccos.png");
    wxBitmap arctan_ = prepareBitMap("./image/arctan.png");
    wxBitmap cos_ = prepareBitMap("./image/cos.png");
    wxBitmap tan_ = prepareBitMap("./image/tan.png");
    wxBitmap cot_ = prepareBitMap("./image/cot.png");
    wxBitmap sec_ = prepareBitMap("./image/sec.png");
    wxBitmap csc_ = prepareBitMap("./image/csc.png");
    wxBitmap arccot_ = prepareBitMap("./image/arccot.png");
    wxBitmap arcsec_ = prepareBitMap("./image/arcsec.png");
    wxBitmap arccsc_ = prepareBitMap("./image/arccsc.png");
    wxBitmap li_ = prepareBitMap("./image/li.png");
    wxBitmap ci_ = prepareBitMap("./image/ci.png");
    wxBitmap si_ = prepareBitMap("./image/si.png");
    wxBitmap squared_ = prepareBitMap("./image/squared.png");
    wxBitmap log10_ = prepareBitMap("./image/log10.png");
    wxBitmap ln_ = prepareBitMap("./image/ln.png");
    wxBitmap frac_ = prepareBitMap("./image/frac.png");
    wxBitmap sqrt_ = prepareBitMap("./image/sqrt.png");
    wxBitmap cubicroot_ = prepareBitMap("./image/cubicroot.png");
    wxBitmap cube_ = prepareBitMap("./image/cube.png");
    wxBitmap pow_ = prepareBitMap("./image/pow.png");
    wxBitmap log_ = prepareBitMap("./image/log.png");
    wxBitmap nthroot_ = prepareBitMap("./image/nthroot.png");
    wxBitmap inversex_ = prepareBitMap("./image/inversex.png");
    wxBitmap sinh_ = prepareBitMap("./image/sinh.png");
    wxBitmap cosh_ = prepareBitMap("./image/cosh.png");
    wxBitmap tanh_ = prepareBitMap("./image/tanh.png");
    wxBitmap sech_ = prepareBitMap("./image/sech.png");
    wxBitmap csch_ = prepareBitMap("./image/csch.png");
    wxBitmap coth_ = prepareBitMap("./image/coth.png");
    wxBitmap arcsinh_ = prepareBitMap("./image/arcsinh.png");
    wxBitmap arccosh_ = prepareBitMap("./image/arccosh.png");
    wxBitmap arctanh_ = prepareBitMap("./image/arctanh.png");
    wxBitmap arcsech_ = prepareBitMap("./image/arcsech.png");
    wxBitmap arccsch_ = prepareBitMap("./image/arccsch.png");
    wxBitmap arccoth_ = prepareBitMap("./image/arccoth.png");
    wxBitmap abs_ = prepareBitMap("./image/abs.png");
    wxBitmap floor_ = prepareBitMap("./image/floor.png");
    wxBitmap ceil_ = prepareBitMap("./image/ceil.png");
    wxBitmap factorial_ = prepareBitMap("./image/factorial.png");
    wxBitmap e_ = prepareBitMap("./image/e.png");
    wxBitmap exp_ = prepareBitMap("./image/exp.png");
    wxBitmap pi_ = prepareBitMap("./image/pi.png");
    wxBitmap shi_ = prepareBitMap("./image/shi.png");
    wxBitmap chi_ = prepareBitMap("./image/chi.png");
    wxBitmap erf_ = prepareBitMap("./image/erf.png");
    wxBitmap erfc_ = prepareBitMap("./image/erfc.png");
    wxBitmap erfi_ = prepareBitMap("./image/erfi.png");
    wxBitmap productlog_ = prepareBitMap("./image/productlog.png");
    wxBitmap productlogapath_ = prepareBitMap("./image/productlogapath.png");
    wxBitmap gamma_ = prepareBitMap("./image/gamma.png");
    wxBitmap zeta_ = prepareBitMap("./image/zeta.png");
    wxBitmap eulertotient_ = prepareBitMap("./image/eulertotient.png");
    wxBitmap round_ = prepareBitMap("./image/round.png");
    wxBitmap derivative_ = prepareBitMap("./image/derivative.png");
    wxBitmap antiderivative_ = prepareBitMap("./image/antiderivative.png");
    wxBitmap n0 = prepareBitMap("./image/0.png");
    wxBitmap n1 = prepareBitMap("./image/1.png");
    wxBitmap n2 = prepareBitMap("./image/2.png");
    wxBitmap n3 = prepareBitMap("./image/3.png");
    wxBitmap n4 = prepareBitMap("./image/4.png");
    wxBitmap n5 = prepareBitMap("./image/5.png");
    wxBitmap n6 = prepareBitMap("./image/6.png");
    wxBitmap n7 = prepareBitMap("./image/7.png");
    wxBitmap n8 = prepareBitMap("./image/8.png");
    wxBitmap n9 = prepareBitMap("./image/9.png");
    wxBitmap dot_ = prepareBitMap("./image/dot.png");
    wxBitmap pow10_ = prepareBitMap("./image/pow10.png");
    wxBitmap sto_ = prepareBitMap("./image/sto.png");
    wxBitmap var_ = prepareBitMap("./image/var.png");
    wxBitmap swap_ = prepareBitMap("./image/swap.png");
    wxBitmap bracketleft_ = prepareBitMap("./image/bracketleft.png");
    wxBitmap bracketright_ = prepareBitMap("./image/bracketright.png");
    wxBitmap dms_ = prepareBitMap("./image/dms.png");
    wxBitmap opt_ = prepareBitMap("./image/opt.png");
    wxBitmap shift_ = prepareBitMap("./image/shift.png");
    wxBitmap alpha_ = prepareBitMap("./image/alpha.png");
    wxBitmap more_ = prepareBitMap("./image/more.png");
    wxBitmap up_ = prepareBitMap("./image/up.png");
    wxBitmap left_ = prepareBitMap("./image/left.png");
    wxBitmap right_ = prepareBitMap("./image/right.png");
    wxBitmap down_ = prepareBitMap("./image/down.png");
    wxBitmap backspace_ = prepareBitMap("./image/backspace.png");
    wxBitmap calc_ = prepareBitMap("./image/calc.png");
    wxBitmap randint_ = prepareBitMap("./image/randint.png");
    wxBitmap rand_ = prepareBitMap("./image/rand.png");
    wxBitmap dash_ = prepareBitMap("./image/dash.png");
    wxBitmap plus_ = prepareBitMap("./image/plus.png");
    wxBitmap minus_ = prepareBitMap("./image/minus.png");
    wxBitmap multiply_ = prepareBitMap("./image/multiply.png");
    wxBitmap divide_ = prepareBitMap("./image/divide.png");
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1000, "", wxPoint(0, 480), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n0);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1001, "", wxPoint(0, 450), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n1);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1002, "", wxPoint(100, 450), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n2);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1003, "", wxPoint(200, 450), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n3);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1004, "", wxPoint(0, 420), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n4);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1005, "", wxPoint(100, 420), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n5);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1006, "", wxPoint(200, 420), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n6);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1007, "", wxPoint(0, 390), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n7);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1008, "", wxPoint(100, 390), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n8);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1009, "", wxPoint(200, 390), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(n9);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1010, "", wxPoint(100, 480), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(dot_);
    FirstPageButton.push_back(std::make_shared<BlackButton>(this, 1011, "", wxPoint(200, 480), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(pow10_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1012, "", wxPoint(0, 360), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(sto_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1013, "", wxPoint(100, 360), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(var_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1014, "", wxPoint(200, 360), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(swap_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1015, "", wxPoint(0, 330), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(bracketleft_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1016, "", wxPoint(100, 330), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(bracketright_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1017, "", wxPoint(200, 330), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(dms_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1018, "", wxPoint(0, 300), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(frac_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1019, "", wxPoint(100, 300), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(sqrt_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1020, "", wxPoint(200, 300), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(cubicroot_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1021, "", wxPoint(0, 270), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(squared_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1022, "", wxPoint(100, 270), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(cube_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1023, "", wxPoint(200, 270), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(pow_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1024, "", wxPoint(0, 240), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(sin_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1025, "", wxPoint(100, 240), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(cos_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1026, "", wxPoint(200, 240), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(tan_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1027, "", wxPoint(0, 210), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(opt_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1028, "", wxPoint(100, 210), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(shift_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1029, "", wxPoint(200, 210), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(alpha_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1030, "", wxPoint(300, 240), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(cot_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1031, "", wxPoint(400, 240), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(sec_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1032, "", wxPoint(500, 240), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(csc_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1033, "", wxPoint(300, 270), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(ln_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1034, "", wxPoint(400, 270), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(log10_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1035, "", wxPoint(500, 270), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(log_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1036, "", wxPoint(300, 300), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(nthroot_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1037, "", wxPoint(400, 300), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(inversex_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1038, "", wxPoint(500, 300), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(factorial_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1039, "", wxPoint(300, 330), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(sinh_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1040, "", wxPoint(400, 330), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(cosh_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1041, "", wxPoint(500, 330), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(tanh_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1042, "", wxPoint(300, 360), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(coth_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1043, "", wxPoint(400, 360), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(sech_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1044, "", wxPoint(500, 360), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(csch_);
    FirstPageButton_ShiftAffect.push_back(FirstPageButton.at(FirstPageButton.size() -1 ));
    FirstPageButton.push_back(std::make_shared<Button>(this, 1045, "", wxPoint(300, 390), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(abs_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1046, "", wxPoint(400, 390), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(round_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1047, "", wxPoint(500, 390), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(floor_);
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1048, "", wxPoint(400, 420), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(up_);
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1049, "", wxPoint(300, 450), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(left_);
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1050, "", wxPoint(500, 450), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(right_);
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1051, "", wxPoint(400, 480), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(down_);
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1052, "", wxPoint(300, 420), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(dash_);
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1053, "", wxPoint(500, 420), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(backspace_);
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1054, "", wxPoint(400, 450), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(calc_);
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1055, "", wxPoint(300, 480), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(randint_);
    FirstPageButton.push_back(std::make_shared<GreenButton>(this, 1056, "", wxPoint(500, 480), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(rand_);
    FirstPageButton.push_back(std::make_shared<OperationButton>(this, 1057, "", wxPoint(600, 480), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(plus_);
    FirstPageButton.push_back(std::make_shared<OperationButton>(this, 1058, "", wxPoint(700, 480), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(minus_);
    FirstPageButton.push_back(std::make_shared<OperationButton>(this, 1059, "", wxPoint(600, 450), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(multiply_);
    FirstPageButton.push_back(std::make_shared<OperationButton>(this, 1060, "", wxPoint(700, 450), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(divide_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1061, "", wxPoint(300, 210), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(e_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1062, "", wxPoint(400, 210), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(exp_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1063, "", wxPoint(500, 210), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(pi_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1064, "", wxPoint(600, 420), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(si_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1065, "", wxPoint(700, 420), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(ci_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1066, "", wxPoint(600, 390), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(shi_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1067, "", wxPoint(700, 390), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(chi_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1068, "", wxPoint(600, 360), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(li_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1069, "", wxPoint(700, 360), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(productlog_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1070, "", wxPoint(600, 330), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(erf_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1071, "", wxPoint(700, 330), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(erfc_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1072, "", wxPoint(600, 300), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(erfi_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1073, "", wxPoint(700, 300), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(gamma_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1074, "", wxPoint(600, 270), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(zeta_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1075, "", wxPoint(700, 270), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(eulertotient_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1076, "", wxPoint(600, 240), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(productlogapath_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1077, "", wxPoint(700, 240), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(antiderivative_);
    FirstPageButton.push_back(std::make_shared<SpecialButton>(this, 1078, "", wxPoint(600, 210), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(derivative_);
    FirstPageButton.push_back(std::make_shared<Button>(this, 1079, "", wxPoint(700, 210), wxSize(100, 30)));
    FirstPageButton[FirstPageButton.size() - 1]->SetBitmap(more_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1080, "", wxPoint(0, 240), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arcsin_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1081, "", wxPoint(100, 240), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arccos_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1082, "", wxPoint(200, 240), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arctan_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1083, "", wxPoint(300, 240), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arccot_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1084, "", wxPoint(400, 240), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arcsec_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1085, "", wxPoint(500, 240), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arccsc_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1086, "", wxPoint(300, 330), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arcsinh_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1087, "", wxPoint(400, 330), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arccosh_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1088, "", wxPoint(500, 330), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arctanh_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1089, "", wxPoint(300, 360), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arccoth_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1090, "", wxPoint(400, 360), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arcsech_);
    FirstPageButton_Shift.push_back(std::make_shared<Button>(this, 1091, "", wxPoint(500, 360), wxSize(100, 30)));
    FirstPageButton_Shift[FirstPageButton_Shift.size() - 1]->SetBitmap(arccsch_);
    for(auto & a: FirstPageButton_Shift.GetContainer())
    {
        a.Hide();
    }
    this->Layout(); // Ensure layout is refreshed
    wxYield();      // Let the system update layout
    for (auto &a : FirstPageButton.GetContainer())
    {
        // push rect
        FirstPageButtonRect.push_back(a.GetRect());
    }
    for (auto &a : FirstPageButton_Shift.GetContainer())
    {
        // push rect
        FirstPageButtonShiftRect.push_back(a.GetRect());
    }
}