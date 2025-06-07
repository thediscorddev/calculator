#pragma once
#include "../wxmathplot/mathplot.h"
#include <wx/wx.h>
#include <memory>
#include "Function_Composed.hpp"
#include <vector>
#include "Xaxis.hpp"
#include "Yaxis.hpp"
enum PenColor
{

};
struct Layer
{
    std::shared_ptr<Function_Composed> function = nullptr;
    MathPlot::mpFXYVector *func = nullptr;
    MathPlot::mpLayer *asLayer() const
    {
        return static_cast<MathPlot::mpLayer *>(func);
    }
};
class Graphing : public wxFrame
{
private:
    MathPlot::mpWindow *mpPlot;
    std::vector<Layer> Vectorlayer;
    void ReloadFunc(Layer *TargetLayer, double minX, double minY, double maxX, double maxY);
    void ReloadGraph();
    Xaxis *xaxis = nullptr;
    Yaxis *yaxis = nullptr;
    Xaxis *xaxis2 = nullptr;
    Yaxis *yaxis2 = nullptr;
    double OldXmin = 0, OldYmin = 0, OldXmax = 0, OldYmax = 0;
    const double maxMovingVelocity = 1.1;
    void reloadAxisRange();
public:
    Graphing(std::shared_ptr<Function_Composed> func_);
    void addFunc(std::shared_ptr<Function_Composed> func);
    void removeFunc(std::shared_ptr<Function_Composed> func);
    void OnMouseRelease(wxMouseEvent &event);
    void OnMouseWheel(wxMouseEvent &event);
};