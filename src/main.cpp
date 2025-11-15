#include <GL/glut.h>
#include "target.h"
#include "arrow.h"
#include <iostream>

Target target(650, 250, 50, false, 0);   // static target
Arrow arrow(120, 120);                   // visible starting position

float lastTime = 0;
float angleDeg = 45.0f;
float power = 300.0f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // ALWAYS visible
    target.draw();
    arrow.draw();

    glutSwapBuffers();
}

void update()
{
    float current = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float dt = current - lastTime;
    lastTime = current;

    target.update(dt);
    arrow.update(dt);

    arrow.checkCollision(target);

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':
            // Shoot arrow from visible position
            arrow.reset(120, 120);
            arrow.shoot(angleDeg, power);
            break;

        case 'a': angleDeg += 2; break;
        case 'd': angleDeg -= 2; break;

        case 'w': power += 20; break;
        case 's': power -= 20; break;

        case 'r': 
            // Reset arrow manually
            arrow.reset(120, 120);
            break;
    }

    std::cout << "Angle: " << angleDeg
              << "   Power: " << power << "\n";
}

void initGL()
{
    glClearColor(0.18f, 0.18f, 0.18f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);  // 2D world
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Arrow + Target Simple Demo");

    initGL();

    lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
