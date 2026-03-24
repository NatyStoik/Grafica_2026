#include "Grid.h"
#include <GL/freeglut.h>
#include <cmath>

namespace
{
    int g_windowWidth = 800;
    int g_windowHeight = 600;

    int g_rows = 20;
    int g_cols = 20;

    float g_cellSize = 20.0f;
    float g_offsetX = 0.0f;
    float g_offsetY = 0.0f;

    constexpr float PI = 3.14159265358979323846f;

    void RecomputeLayout()
    {
        float cellW = (float)g_windowWidth / (float)g_cols;
        float cellH = (float)g_windowHeight / (float)g_rows;

        g_cellSize = (cellW < cellH) ? cellW : cellH;

        float gridPixelWidth = g_cellSize * g_cols;
        float gridPixelHeight = g_cellSize * g_rows;

        g_offsetX = ((float)g_windowWidth - gridPixelWidth) * 0.5f;
        g_offsetY = ((float)g_windowHeight - gridPixelHeight) * 0.5f;
    }

    float GridPointX(int x)
    {
        return g_offsetX + x * g_cellSize;
    }

    float GridPointY(int y)
    {
        return g_offsetY + y * g_cellSize;
    }

    void DrawDiscAtScreen(float cx, float cy, float radius)
    {
        const int segments = 32;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);

        for (int i = 0; i <= segments; i++)
        {
            float angle = 2.0f * PI * (float)i / (float)segments;
            float x = cx + radius * cosf(angle);
            float y = cy + radius * sinf(angle);
            glVertex2f(x, y);
        }

        glEnd();
    }
}

void Grid_SetWindowSize(int width, int height)
{
    g_windowWidth = (width > 1) ? width : 1;
    g_windowHeight = (height > 1) ? height : 1;
    RecomputeLayout();
}

void Grid_SetSize(int rows, int cols)
{
    g_rows = (rows > 0) ? rows : 1;
    g_cols = (cols > 0) ? cols : 1;
    RecomputeLayout();
}

void Grid_BeginFrame()
{
    glViewport(0, 0, g_windowWidth, g_windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)g_windowWidth, 0.0, (double)g_windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Grid_Draw()
{
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);

    for (int c = 0; c <= g_cols; c++)
    {
        float x = g_offsetX + c * g_cellSize;
        glVertex2f(x, g_offsetY);
        glVertex2f(x, g_offsetY + g_rows * g_cellSize);
    }

    for (int r = 0; r <= g_rows; r++)
    {
        float y = g_offsetY + r * g_cellSize;
        glVertex2f(g_offsetX, y);
        glVertex2f(g_offsetX + g_cols * g_cellSize, y);
    }

    glEnd();
}

void Grid_DrawPixel(int x, int y)
{
    if (x < 0 || x > g_cols || y < 0 || y > g_rows)
        return;

    float cx = GridPointX(x);
    float cy = GridPointY(y);

    float radius = 0.22f * g_cellSize;

    glColor3f(0.0f, 0.0f, 0.0f);
    DrawDiscAtScreen(cx, cy, radius);
}

void Grid_DrawVirtualLine(int x0, int y0, int x1, int y1)
{
    float sx0 = GridPointX(x0);
    float sy0 = GridPointY(y0);
    float sx1 = GridPointX(x1);
    float sy1 = GridPointY(y1);

    glColor3f(0.1f, 0.2f, 0.95f);
    glLineWidth(3.0f);

    glBegin(GL_LINES);
    glVertex2f(sx0, sy0);
    glVertex2f(sx1, sy1);
    glEnd();
}

void Grid_DrawHorizontalSpan(int y, int x0, int x1)
{
    if (x0 > x1)
    {
        int t = x0; x0 = x1; x1 = t;
    }

    for (int x = x0; x <= x1; x++)
        Grid_DrawPixel(x, y);
}

void Grid_DrawVirtualCircle(int cx, int cy, int radius)
{
    float scx = GridPointX(cx);
    float scy = GridPointY(cy);
    float sr = radius * g_cellSize;

    glColor3f(0.1f, 0.2f, 0.95f);
    glLineWidth(3.0f);

    const int segments = 128;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        float angle = 2.0f * PI * (float)i / (float)segments;
        float x = scx + sr * cosf(angle);
        float y = scy + sr * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}
