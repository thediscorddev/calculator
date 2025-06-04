#pragma once
#include "../wxmathplot/mathplot.h"
class Yaxis : public MathPlot::mpScaleY
{
public:
    Yaxis(const wxString &name = _T("X"), int flags = mpALIGN_CENTERX, bool grids = false, unsigned int type = mpX_NORMAL) : mpScaleY(name, flags, grids, type) {};
    double getMinY(MathPlot::mpWindow *w)
    {
        int orgx = GetOrigin(*w);
        if (orgx == -1)
            return -1;
        const double scaleY = w->GetScaleY(m_isY2Axis);
        const double posY = w->GetPosY(m_isY2Axis);
        return (posY - (double)(w->GetScreenY()) / scaleY);
    }
    double getMaxY(MathPlot::mpWindow *w)
    {
        int orgx = GetOrigin(*w);

        // Draw nothing if we are outside margins
        if (orgx == -1)
            return -1;
        const double scaleY = w->GetScaleY(m_isY2Axis);
        const double posY = w->GetPosY(m_isY2Axis);
        const double end = posY + (double)w->GetScreenY() / scaleY;
        return end;
    }
};