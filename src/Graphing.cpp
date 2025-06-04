#include "../scr/Graphing.hpp"
#include <TMATH/t_math.hpp>
#include <iostream>
Graphing::Graphing(std::shared_ptr<Function_Composed> func_) : wxFrame(nullptr, wxID_ANY, "Thein calculator: Graph", wxDefaultPosition, wxSize(800, 600))
{
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    // Create plot control
    mpPlot = new MathPlot::mpWindow(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600));
    sizer->Add(mpPlot, 1, wxEXPAND | wxALL, 5);

    // Create a plot layer for the function
    MathPlot::mpFXYVector *func = new MathPlot::mpFXYVector();

    // Define range and step
    func->SetDrawOutsideMargins(false);
    func->SetContinuity(true);

    // Fill data points for f(x) = cos(cos(tan(x)))
    const int points = 1000;
    const double xmin = -11;
    const double xmax = 11;

    double step = (xmax - xmin) / points;
    mpPlot->SetPos(0, 0, 0);
    mpPlot->SetScaleX(10);
    mpPlot->SetScaleY(50);
    MathPlot::mpFloatRect rect;
    rect.Xmin = -10;
    rect.Xmax = 10;
    rect.Ymin = -20;
    rect.Ymax = 20;
    rect.Y2min = -20;
    rect.Y2max = 20;
    for (int i = 0; i <= points; ++i)
    {
        try
        {
            double x = xmin + i * step;
            double y = std::stod(func_->Calculate(x).GetData());
            func->AddData(x, y, false);
        }
        catch (...)
        {
        }
    }

    func->SetPen(*wxBLUE_PEN);
    func->SetDrawOutsideMargins(false);
    func->SetContinuity(true);
    mpPlot->Fit(rect);
    xaxis = new Xaxis("X", mpALIGN_CENTERX, true, mpX_NORMAL);
    xaxis2 = new Xaxis("X", mpALIGN_BOTTOM, false, mpX_NORMAL);
    yaxis = new Yaxis("Y", mpALIGN_CENTERY, true);
    yaxis2 = new Yaxis("Y", mpALIGN_LEFT, false);
    mpPlot->AddLayer(xaxis);
    mpPlot->AddLayer(yaxis);
    mpPlot->AddLayer(yaxis2);
    mpPlot->AddLayer(xaxis2);
    mpPlot->AddLayer(func);

    // Enable zoom with mouse wheel & box zoom
    mpPlot->EnableMousePanZoom(true);
    // mpPlot->SetMPScrollbars(true);
    //  mpPlot->EnableDrag(true);
    SetSizer(sizer);
    mpPlot->Bind(wxEVT_LEFT_UP, &Graphing::OnMouseRelease, this);
    mpPlot->Bind(wxEVT_RIGHT_UP, &Graphing::OnMouseRelease, this);
    mpPlot->Bind(wxEVT_MOUSEWHEEL, &Graphing::OnMouseWheel, this);
    std::cout << "Axis minX min scale before in: " << xaxis->GetMinScale() << ", maxX before in: " << xaxis->GetMaxScale() << "\n";
    Layer newLayer;
    newLayer.function = func_;
    newLayer.func = func;
    Vectorlayer.push_back(newLayer);
    reloadAxisRange();
}
void Graphing::addFunc(std::shared_ptr<Function_Composed> func)
{
    Layer newLayer;
    newLayer.function = func;
    newLayer.func = new MathPlot::mpFXYVector();
    newLayer.func->SetDrawOutsideMargins(false);
    newLayer.func->SetContinuity(true);
    newLayer.func->SetPen(*wxBLUE_PEN);
    newLayer.func->SetDrawOutsideMargins(false);
    newLayer.func->SetContinuity(true);
    int width, height;
    mpPlot->GetClientSize(&width, &height); // width = pixels along x, height = pixels along y

    double x_min = xaxis->getMinX(mpPlot) - 1;
    double x_max = xaxis->getMaxX(mpPlot) + 1;

    double y_min = yaxis->getMinY(mpPlot) - 1;
    double y_max = yaxis->getMaxY(mpPlot) + 1;
    double step = (x_max - x_min) / 1000;
    for (int i = 0; i <= 1000; ++i)
    {
        try
        {
            double x = x_min + i * step;
            double y = std::stod(newLayer.function->Calculate(x).GetData());
            if (y < y_max && y > y_min)
                newLayer.func->AddData(x, y, false);
        }
        catch (...)
        {
        }
    }
    mpPlot->AddLayer(newLayer.func);
    mpPlot->UpdateAll();
    Vectorlayer.push_back(newLayer);
}
void Graphing::removeFunc(std::shared_ptr<Function_Composed> func)
{
    int elnum = -1;
    for (int i = 0; i < Vectorlayer.size(); i++)
    {
        if (Vectorlayer.at(i).function == func)
        {
            elnum = i;
            mpPlot->DelLayer(Vectorlayer.at(i).asLayer(), true, false);
            Vectorlayer.at(i).func = nullptr;
            mpPlot->UpdateAll();
            break;
        }
    }
    if (elnum >= 0)
    {
        Vectorlayer.erase(Vectorlayer.begin() + elnum);
    }
}
void Graphing::ReloadGraph()
{
    double x_min = xaxis->getMinX(mpPlot) - 1;
    double x_max = xaxis->getMaxX(mpPlot) + 1;
    double y_min = yaxis->getMinY(mpPlot) - 1;
    double y_max = yaxis->getMaxY(mpPlot) + 1;

    /*bool Needupdate = false;

    // Helper for direction: returns 1 if positive delta, -1 if negative
    auto sign = [](double x)
    { return x > 0 ? 1 : -1; };

    // X MAX
    double Vxmax = t_math::abs(x_max - OldXmax);
    if (Vxmax > maxMovingVelocity)
    {
        Needupdate = true;
        int direction = sign(x_max - OldXmax);
        x_max = OldXmax + direction * maxMovingVelocity;
    }

    // X MIN
    double Vxmin = t_math::abs(x_min - OldXmin);
    if (Vxmin > maxMovingVelocity)
    {
        Needupdate = true;
        int direction = sign(x_min - OldXmin);
        x_min = OldXmin + direction * maxMovingVelocity;
    }

    // Y MAX
    double Vymax = t_math::abs(y_max - OldYmax);
    if (Vymax > maxMovingVelocity)
    {
        Needupdate = true;
        int direction = sign(y_max - OldYmax);
        y_max = OldYmax + direction * maxMovingVelocity;
    }

    // Y MIN
    double Vymin = t_math::abs(y_min - OldYmin);
    if (Vymin > maxMovingVelocity)
    {
        Needupdate = true;
        int direction = sign(y_min - OldYmin);
        y_min = OldYmin + direction * maxMovingVelocity;
    }

    // Clamp zoom range to avoid overload
    if ((x_max - x_min) > 500.0)
    {
        Needupdate = true;
        double center = (x_min + x_max) / 2.0;
        x_min = center - 250.0;
        x_max = center + 250.0;
    }
    if ((y_max - y_min) > 1000.0)
    {
        Needupdate = true;
        double center = (y_min + y_max) / 2.0;
        y_min = center - 500.0;
        y_max = center + 500.0;
    }

    // Only apply Fit() when needed
    if (Needupdate)
    {
        MathPlot::mpFloatRect rect;
        rect.Xmin = x_min;
        rect.Xmax = x_max;
        rect.Ymin = y_min;
        rect.Ymax = y_max;
        rect.Y2min = y_min;
        rect.Y2max = y_max;
        mpPlot->Fit(rect);

        // Update old bounds
        reloadAxisRange();
    }*/
    for (auto &el : Vectorlayer)
    {
        if (el.func)
        {
            mpPlot->DelLayer(el.func, true, false);
            el.func = nullptr;
        }
    }
    // Reload function layers properly
    for (auto &el : Vectorlayer)
    {
        ReloadFunc(&el, x_min, y_min, x_max, y_max);
    }

    mpPlot->UpdateAll();
}
void Graphing::ReloadFunc(Layer *TargetLayer, double minX, double minY, double maxX, double maxY)
{
    // Remove old layer if exists
    if (TargetLayer->func)
    {
        mpPlot->DelLayer(TargetLayer->func, true, false);
        delete TargetLayer->func;
        TargetLayer->func = nullptr;
    }

    // Create new mpFXYVector and fill data
    TargetLayer->func = new MathPlot::mpFXYVector();
    TargetLayer->func->SetDrawOutsideMargins(false);
    TargetLayer->func->SetContinuity(true);
    TargetLayer->func->SetPen(*wxBLUE_PEN);

    double step = (maxX - minX) / 1000;
    for (int i = 0; i <= 1000; ++i)
    {
        try
        {
            double x = minX + i * step;
            double y = std::stod(TargetLayer->function->Calculate(x).GetData());
            if (y < maxY && y > minY)
                TargetLayer->func->AddData(x, y, false);
        }
        catch (...)
        {
        }
    }
    mpPlot->AddLayer(TargetLayer->func);
}

void Graphing::OnMouseRelease(wxMouseEvent &event)
{
    ReloadGraph();
    event.Skip(); // let mpWindow handle it too
}

void Graphing::OnMouseWheel(wxMouseEvent &event)
{
    event.Skip(); // zoom happens here
    CallAfter([=]()
              { ReloadGraph(); });
}
void Graphing::reloadAxisRange()
{
    OldXmin = xaxis->getMinX(mpPlot);
    OldXmax = xaxis->getMaxX(mpPlot);
    OldYmin = yaxis->getMinY(mpPlot);
    OldYmax = yaxis->getMaxY(mpPlot);
}