#pragma once
#include "../wxmathplot/mathplot.h"
class Xaxis : public MathPlot::mpScaleX
{
public:
    Xaxis(const wxString &name = _T("X"), int flags = mpALIGN_CENTERX, bool grids = false, unsigned int type = mpX_NORMAL) : mpScaleX(name, flags, grids, type) {};
    double getMinX(MathPlot::mpWindow * w)
    {
        int orgy = GetOrigin(*w);

        // Draw nothing if we are outside margins
        if (orgy == -1)
            return -1;
        return w->GetPosX();
    }
    double getMaxX(MathPlot::mpWindow * w)
    {
        int orgy = GetOrigin(*w);

        // Draw nothing if we are outside margins
        if (orgy == -1)
            return -1;
        const double scaleX = w->GetScaleX();
        const double step = GetStep(scaleX);
        const double end = w->GetPosX() + (double)w->GetScreenX() / scaleX;
        return end;
    }
};