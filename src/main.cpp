#include <GL/glut.h>
#include <iostream>
#include "bow.h"
#include "target.h"
#include "Barrier.h"

Bow bow(120, 120);
Target target(650, 250, 50, false, 0);

// Create a barrier at center region
// x=400, y=200, width=40, height=120, moving vertically
Barrier barrier(400, 200, 40, 120, true);

float lastTime = 0;

// Check all collisions: arrow–target and arrow–barrier
void checkCollisions()
{
    for (auto &arrow : bow.getArrows())
    {
        // Target collision
        arrow.checkCollision(target);

        // Barrier collision
        if (barrier.checkCollision(arrow.getX(), arrow.getY()))
        {
            arrow.deactivate();       // stop flying
            arrow.setHit(false);      // arrow disappears (no hit pose)
            std::cout << "Arrow hit barrier!\n";
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    bow.draw();
    target.draw();
    barrier.draw();   // draw the barrier

    glutSwapBuffers();
}

void update()
{
    float current = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = current - lastTime;
    lastTime = current;

    bow.update(dt);
    target.update(dt);
    barrier.update(dt);   // update barrier movement

    checkCollisions();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ': bow.startCharge(); break;

        case 'w': bow.aimUp();    break;
        case 's': bow.aimDown();  break;
        case 'a': bow.decreasePower(); break;
        case 'd': bow.increasePower(); break;

        case 'r': bow.getArrows().clear(); break;

        // toggle moving barrier
        case 'm': barrier.setMoving(true);  break;
        case 'n': barrier.setMoving(false); break;
    }
}

void keyboardUp(unsigned char key, int, int)
{
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
    glutCreateWindow("Archery_Game_OpenGL_With_Barrier");

    initGL();

    lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);

    glutMainLoop();
    return 0;
}
