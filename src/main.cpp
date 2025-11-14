#include <GL/glut.h>
#include "target.h"

Target target(650, 250, 50, false, 0.0f);

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    target.draw();

    glutSwapBuffers();
}

void initGL() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Archery Game OpenGL");

    initGL();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
