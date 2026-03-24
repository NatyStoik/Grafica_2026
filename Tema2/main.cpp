#include <GL/freeglut.h>
#include "Grid.h"
#include "Line.h"
#include "Circle.h"

int g_windowWidth = 900;
int g_windowHeight = 700;
int g_demoMode = 1;

void UpdateWindowTitle()
{
    switch (g_demoMode)
    {
    case 1:
        glutSetWindowTitle("Demo 1 - Polygon gros Bresenham");
        break;
    case 2:
        glutSetWindowTitle("Demo 2 - Toate octantele liniei");
        break;
    case 3:
        glutSetWindowTitle("Demo 3 - Cerc midpoint contur");
        break;
    case 4:
        glutSetWindowTitle("Demo 4 - Cerc midpoint umplut");
        break;
    default:
        glutSetWindowTitle("Tema - Bresenham Midpoint");
        break;
    }
}

void Display()
{
    Grid_BeginFrame();
    Grid_Draw();

    switch (g_demoMode)
    {
    case 1:
        DrawLineDemoPolygon();
        break;
    case 2:
        DrawLineDemoAllOctants();
        break;
    case 3:
        DrawCircleDemoOutline();
        break;
    case 4:
        DrawCircleDemoFilled();
        break;
    default:
        DrawLineDemoPolygon();
        break;
    }

    glFlush();
}

void Reshape(int width, int height)
{
    g_windowWidth = width;
    g_windowHeight = height;
    Grid_SetWindowSize(width, height);
    glutPostRedisplay();
}

void Keyboard(unsigned char key, int, int)
{
    switch (key)
    {
    case '1':
        g_demoMode = 1;
        UpdateWindowTitle();
        glutPostRedisplay();
        break;
    case '2':
        g_demoMode = 2;
        UpdateWindowTitle();
        glutPostRedisplay();
        break;
    case '3':
        g_demoMode = 3;
        UpdateWindowTitle();
        glutPostRedisplay();
        break;
    case '4':
        g_demoMode = 4;
        UpdateWindowTitle();
        glutPostRedisplay();
        break;
    case 27:
        glutLeaveMainLoop();
        break;
    }
}

void Init()
{
    Grid_SetSize(40, 40);
    Grid_SetWindowSize(g_windowWidth, g_windowHeight);
    UpdateWindowTitle();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(g_windowWidth, g_windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tema - Bresenham Midpoint");

    Init();
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();

    return 0;
}
