#include "Line.h"
#include "Grid.h"
#include <cstdlib>

namespace
{
    void PlotLine_PosLow(int x0, int y0, int x1, int y1)
    {
        // 0 <= slope <= 1, x creste, y creste
        int dx = x1 - x0;
        int dy = y1 - y0;

        int d = 2 * dy - dx;
        int dE = 2 * dy;
        int dNE = 2 * (dy - dx);

        int x = x0;
        int y = y0;

        Grid_DrawPixel(x, y);

        while (x < x1)
        {
            if (d <= 0)
            {
                d += dE;
            }
            else
            {
                d += dNE;
                y++;
            }

            x++;
            Grid_DrawPixel(x, y);
        }
    }

    void PlotLine_PosHigh(int x0, int y0, int x1, int y1)
    {
        // slope > 1, y creste, x creste
        int dx = x1 - x0;
        int dy = y1 - y0;

        int d = 2 * dx - dy;
        int dN = 2 * dx;
        int dNE = 2 * (dx - dy);

        int x = x0;
        int y = y0;

        Grid_DrawPixel(x, y);

        while (y < y1)
        {
            if (d <= 0)
            {
                d += dN;
            }
            else
            {
                d += dNE;
                x++;
            }

            y++;
            Grid_DrawPixel(x, y);
        }
    }

    void PlotLine_NegLow(int x0, int y0, int x1, int y1)
    {
        // -1 <= slope < 0, x creste, y scade
        int dx = x1 - x0;
        int ay = y0 - y1;   // = -dy, pozitiv

        int d = 2 * ay - dx;
        int dE = 2 * ay;
        int dSE = 2 * (ay - dx);

        int x = x0;
        int y = y0;

        Grid_DrawPixel(x, y);

        while (x < x1)
        {
            if (d <= 0)
            {
                d += dE;
            }
            else
            {
                d += dSE;
                y--;
            }

            x++;
            Grid_DrawPixel(x, y);
        }
    }

    void PlotLine_NegHigh(int x0, int y0, int x1, int y1)
    {
        // slope < -1, y creste, x scade
        int ax = x0 - x1;   // = -dx, pozitiv
        int dy = y1 - y0;

        int d = 2 * ax - dy;
        int dN = 2 * ax;
        int dNW = 2 * (ax - dy);

        int x = x0;
        int y = y0;

        Grid_DrawPixel(x, y);

        while (y < y1)
        {
            if (d <= 0)
            {
                d += dN;
            }
            else
            {
                d += dNW;
                x--;
            }

            y++;
            Grid_DrawPixel(x, y);
        }
    }
}

void RasterizeLineMidpoint(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    // caz degenerat: un singur punct
    if (dx == 0 && dy == 0)
    {
        Grid_DrawPixel(x0, y0);
        return;
    }

    // verticala
    if (dx == 0)
    {
        if (y0 > y1)
        {
            int t = y0; y0 = y1; y1 = t;
        }

        for (int y = y0; y <= y1; y++)
            Grid_DrawPixel(x0, y);

        return;
    }

    // orizontala
    if (dy == 0)
    {
        if (x0 > x1)
        {
            int t = x0; x0 = x1; x1 = t;
        }

        for (int x = x0; x <= x1; x++)
            Grid_DrawPixel(x, y0);

        return;
    }

    // 1) panta pozitiva
    if ((dx > 0 && dy > 0) || (dx < 0 && dy < 0))
    {
        // daca linia merge spre stanga, inversam capetele
        if (x0 > x1)
        {
            int t = x0; x0 = x1; x1 = t;
            t = y0; y0 = y1; y1 = t;
        }

        dx = x1 - x0;
        dy = y1 - y0;

        if (dy <= dx)
            PlotLine_PosLow(x0, y0, x1, y1);
        else
            PlotLine_PosHigh(x0, y0, x1, y1);

        return;
    }

    // 2) panta negativa
    if (x0 < x1)
    {
        dx = x1 - x0;
        dy = y1 - y0;

        if (-dy <= dx)
            PlotLine_NegLow(x0, y0, x1, y1);
        else
        {
            // vrem forma: y creste, x scade
            RasterizeLineMidpoint(x1, y1, x0, y0);
        }
    }
    else
    {
        dx = x1 - x0;
        dy = y1 - y0;

        if (dy <= -dx)
        {
            // vrem forma: x creste, y scade
            RasterizeLineMidpoint(x1, y1, x0, y0);
        }
        else
            PlotLine_NegHigh(x0, y0, x1, y1);
    }
}

void DrawLineDemoAllOctants()
{
    const int cx = 15;
    const int cy = 15;

    const int pts[8][2] =
    {
        {24, 19}, // octant 1
        {19, 24}, // octant 2
        {11, 24}, // octant 3
        { 6, 19}, // octant 4
        { 6, 11}, // octant 5
        {11,  6}, // octant 6
        {19,  6}, // octant 7
        {24, 11}  // octant 8
    };

    for (int i = 0; i < 8; i++)
    {
        int x = pts[i][0];
        int y = pts[i][1];

        Grid_DrawVirtualLine(cx, cy, x, y);
        RasterizeLineMidpoint(cx, cy, x, y);
    }
}

void DrawLineDemoPolygon()
{
    const int points[][2] =
    {
        { 8, 18},
        {12, 26},
        {20, 29},
        {28, 27},
        {33, 18},
        {31, 10},
        {23,  6},
        {14,  7},
        { 9, 12}
    };

    const int count = sizeof(points) / sizeof(points[0]);

    for (int i = 0; i < count; i++)
    {
        int j = (i + 1) % count;

        int x0 = points[i][0];
        int y0 = points[i][1];
        int x1 = points[j][0];
        int y1 = points[j][1];

        Grid_DrawVirtualLine(x0, y0, x1, y1);
        RasterizeLineMidpointThick(x0, y0, x1, y1, 3);
    }


}

void RasterizeLineMidpointThick(int x0, int y0, int x1, int y1, int thickness)
{
    if (thickness < 1)
        thickness = 1;

    int dx = x1 - x0;
    int dy = y1 - y0;

    int radius = thickness / 2;

    if (abs(dx) >= abs(dy))
    {
        // linie mai mult orizontala -> grosime pe y
        for (int off = -radius; off <= radius; off++)
            RasterizeLineMidpoint(x0, y0 + off, x1, y1 + off);
    }
    else
    {
        // linie mai mult verticala -> grosime pe x
        for (int off = -radius; off <= radius; off++)
            RasterizeLineMidpoint(x0 + off, y0, x1 + off, y1);
    }
}
