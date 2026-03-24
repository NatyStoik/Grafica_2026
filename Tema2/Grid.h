#pragma once

void Grid_SetWindowSize(int width, int height);
void Grid_SetSize(int rows, int cols);

void Grid_BeginFrame();
void Grid_Draw();

void Grid_DrawPixel(int x, int y);
void Grid_DrawPixelGray(int x, int y);     // opțional, pentru stilul din poze
void Grid_DrawHorizontalSpan(int y, int x0, int x1);

void Grid_DrawVirtualLine(int x0, int y0, int x1, int y1);
void Grid_DrawVirtualCircle(int cx, int cy, int radius);
