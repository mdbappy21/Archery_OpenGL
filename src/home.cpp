#include "home_screen.h"
#include <GL/glut.h>

bool homeScreenActive = true;

// Check if home screen active
bool isHomeScreen()
{
    return homeScreenActive;
}

// Switch off home screen
void exitHomeScreen()
{
    homeScreenActive = false;
}

// Draw a simple button with text
void drawButton(float x, float y, float w, float h, const char* text)
{
    glColor3f(0.2f, 0.5f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x+w, y);
    glVertex2f(x+w, y+h);
    glVertex2f(x, y+h);
    glEnd();

    glColor3f(1, 1, 1);
    glRasterPos2f(x + w/3, y + h/3);
    for(const char* c = text; *c; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void drawHomeScreen()
{
    glClearColor(0.1f, 0.12f, 0.15f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Title
    glColor3f(1, 1, 1);
    glRasterPos2f(300, 500);
    const char *title = "ARCHERY GAME";
    for (int i = 0; title[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, title[i]);

    // Buttons
    drawButton(300, 350, 200, 50, "Play");
    drawButton(300, 260, 200, 50, "Exit");

    glutSwapBuffers();
}

void homeMouse(int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    int mx = x;
    int my = 600 - y; // invert Y because GLUT origin is bottom-left

    // Play button region
    if (mx >= 300 && mx <= 500 && my >= 350 && my <= 400)
    {
        exitHomeScreen();
    }

    // Exit button region
    if (mx >= 300 && mx <= 500 && my >= 260 && my <= 310)
    {
        exit(0);
    }
}
