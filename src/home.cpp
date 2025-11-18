#include <GL/glut.h>

bool showHome = true;

// --------------------------------------------------
// Utility: Draw text at (x, y)
// --------------------------------------------------
void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);
    for (int i = 0; text[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

// --------------------------------------------------
// Utility: Rectangle Button
// --------------------------------------------------
bool drawButton(float x, float y, float w, float h, const char* label)
{
    // Box
    glColor3f(0.22, 0.45, 0.75);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x+w, y);
        glVertex2f(x+w, y+h);
        glVertex2f(x, y+h);
    glEnd();

    // Label
    glColor3f(1, 1, 1);
    drawText(x + w * 0.32f, y + h * 0.33f, label);

    return true;
}

// --------------------------------------------------
// BRAND NEW HOME SCREEN
// --------------------------------------------------
void renderHome()
{
    glClearColor(0.07f, 0.1f, 0.12f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Title
    glColor3f(1, 1, 1);
    drawText(280, 520, "ARCHERY MASTER");

    // Buttons
    drawButton(280, 380, 240, 60, "Start Game");
    drawButton(280, 280, 240, 60, "Quit");

    glutSwapBuffers();
}

// --------------------------------------------------
// Mouse Detection (NEW CLEAN LOGIC)
// --------------------------------------------------
void homeMouse(int btn, int st, int x, int y)
{
    if (btn != GLUT_LEFT_BUTTON || st != GLUT_DOWN) return;

    // Convert to OpenGL coords
    int mx = x;
    int my = 600 - y;

    // Start button box
    if (mx >= 280 && mx <= 520 && my >= 380 && my <= 440)
    {
        showHome = false;        // SWITCH OFF HOME SCREEN
    }

    // Quit box
    if (mx >= 280 && mx <= 520 && my >= 280 && my <= 340)
    {
        exit(0);
    }
}

// --------------------------------------------------
// IDLE → Real-time redraw
// --------------------------------------------------
void update()
{
    if (showHome)
        glutPostRedisplay();
}
