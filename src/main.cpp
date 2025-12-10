// FILE: src/main.cpp
#include <GL/glut.h>
#include "game_manager.h"
#include "input_handler.h"

const int WIN_W = 800;
const int WIN_H = 600;
static GameManager *game = nullptr;
static double lastTime = 0.0;

void display() { if (game) game->render(); }

void reshape(int w, int h) {
    // keep fixed logical size: always set viewport to WIN_W x WIN_H and project accordingly
    glViewport(0,0,WIN_W,WIN_H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_W, 0, WIN_H);
    glMatrixMode(GL_MODELVIEW);

    if (game) game->resize(WIN_W, WIN_H);
}

void timerFunc(int) {
    double now = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double dt = now - lastTime;
    if (dt < 0) dt = 0;
    lastTime = now;
    if (game) game->update((float)dt);
    glutPostRedisplay();
    glutTimerFunc(16, timerFunc, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Archery Game 2026 - Modular");

    // prevent window resizing (GLUT: remove resize callback or force viewport as above)
    // Note: GLUT itself doesn't provide easily to disable resize; controlling reshape keeps content fixed.

    game = new GameManager(WIN_W, WIN_H);
    game->init();

    // register with input handler
    InputHandler::setGameManager(game);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(InputHandler::keyboardDown);
    glutKeyboardUpFunc(InputHandler::keyboardUp);
    glutSpecialFunc(InputHandler::specialKey);
    glutMouseFunc(InputHandler::mouseClick);

    lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    glutTimerFunc(16, timerFunc, 0);
    glutMainLoop();

    delete game;
    return 0;
}
