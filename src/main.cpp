#include <GL/glut.h>
#include <iostream>
#include "bow.h"
#include "target.h"
#include "home_screen.h"

Bow bow(120, 120);
Target target(650, 250, 50, false, 0);

float lastTime = 0;

void checkArrowTargetCollision()
{
    for (auto &arrow : bow.getArrows())
        arrow.checkCollision(target);
}

void display()
{
    if (isHomeScreen())
    {
        drawHomeScreen();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    bow.draw();
    target.draw();

    glutSwapBuffers();
}

void update()
{
    if (isHomeScreen())
    {
        glutPostRedisplay();
        return;
    }

    float current = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = current - lastTime;
    lastTime = current;

    bow.update(dt);
    target.update(dt);
    checkArrowTargetCollision();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (isHomeScreen()) return;

    switch (key)
    {
        case ' ': bow.startCharge(); break;
        case 'w': bow.aimUp(); break;
        case 's': bow.aimDown(); break;
        case 'a': bow.decreasePower(); break;
        case 'd': bow.increasePower(); break;
        case 'r': bow.getArrows().clear(); break;
    }
}

void keyboardUp(unsigned char key, int, int)
{
    if (isHomeScreen()) return;

    if (key == ' ')
        bow.releaseCharge();
}

void initGL()
{
    glClearColor(0.15f, 0.15f, 0.18f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    bow.setGravity(-400.0f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Archery Game");

    initGL();

    lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(homeMouse);

    glutMainLoop();
    return 0;
}
