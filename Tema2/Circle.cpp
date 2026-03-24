#include "Circle.h"
#include "Grid.h"

namespace
{
    void PlotCircleOctantPair1(int cx, int cy, int x, int y)
    {
        Grid_DrawPixel(cx + x, cy + y);
        Grid_DrawPixel(cx - x, cy + y);
    }

    void PlotCircleOctantPair2(int cx, int cy, int x, int y)
    {
        Grid_DrawPixel(cx + x, cy - y);
        Grid_DrawPixel(cx - x, cy - y);
    }

    void PlotCircleOctantPair3(int cx, int cy, int x, int y)
    {
        Grid_DrawPixel(cx + y, cy + x);
        Grid_DrawPixel(cx - y, cy + x);
    }

    void PlotCircleOctantPair4(int cx, int cy, int x, int y)
    {
        Grid_DrawPixel(cx + y, cy - x);
        Grid_DrawPixel(cx - y, cy - x);
    }

    void PlotCircleAllOctants(int cx, int cy, int x, int y)
    {
        PlotCircleOctantPair1(cx, cy, x, y);
        PlotCircleOctantPair2(cx, cy, x, y);
        PlotCircleOctantPair3(cx, cy, x, y);
        PlotCircleOctantPair4(cx, cy, x, y);
    }

    void FillCircleSpans(int cx, int cy, int x, int y)
    {
        Grid_DrawHorizontalSpan(cy + y, cx - x, cx + x);
        Grid_DrawHorizontalSpan(cy - y, cx - x, cx + x);

        Grid_DrawHorizontalSpan(cy + x, cx - y, cx + y);
        Grid_DrawHorizontalSpan(cy - x, cx - y, cx + y);
    }
}

void RasterizeCircleMidpoint(int cx, int cy, int radius)
{
    if (radius < 0)
        return;

    if (radius == 0)
    {
        Grid_DrawPixel(cx, cy);
        return;
    }

    int x = 0;
    int y = radius;
    int d = 1 - radius;

    PlotCircleAllOctants(cx, cy, x, y);

    while (x < y)
    {
        if (d < 0)
        {
            d = d + 2 * x + 3;
        }
        else
        {
            d = d + 2 * (x - y) + 5;
            y--;
        }

        x++;
        PlotCircleAllOctants(cx, cy, x, y);
    }
}

void RasterizeCircleMidpointFilled(int cx, int cy, int radius)
{
    if (radius < 0)
        return;

    if (radius == 0)
    {
        Grid_DrawPixel(cx, cy);
        return;
    }

    int x = 0;
    int y = radius;
    int d = 1 - radius;

    FillCircleSpans(cx, cy, x, y);

    while (x < y)
    {
        if (d < 0)
        {
            d = d + 2 * x + 3;
        }
        else
        {
            d = d + 2 * (x - y) + 5;
            y--;
        }

        x++;
        FillCircleSpans(cx, cy, x, y);
    }
}

void DrawCircleDemoOutline()
{
    const int cx = 20;
    const int cy = 20;
    const int r = 18;

    Grid_DrawVirtualCircle(cx, cy, r);
    RasterizeCircleMidpoint(cx, cy, r);
}

void DrawCircleDemoFilled()
{
    const int cx = 20;
    const int cy = 20;
    const int r = 18;

    Grid_DrawVirtualCircle(cx, cy, r);
    RasterizeCircleMidpointFilled(cx, cy, r);
}
