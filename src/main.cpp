// main.cpp  (reshape removed — fixed startup projection)
#include <GL/glut.h>
#include "game_manager.h"
#include "input_handler.h"
#include "sound_manager.h"

// initial (fixed) window size
static int WIN_W = 800;
static int WIN_H = 600;

static GameManager *game = nullptr;
static double lastTime = 0.0;

void display() {
    if (game) game->render();
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

int main(int argc, char** argv)
{
    // Initialize GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIN_W, WIN_H);
    glutCreateWindow("Archery Game 2026 - Fixed Projection (no reshape)");

    // --- Set projection & viewport ONCE here (no reshape callback) ---
    glViewport(0, 0, WIN_W, WIN_H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_W, 0, WIN_H);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // -----------------------------------------------------------------

    // Register display and input callbacks
    glutDisplayFunc(display);
    // Note: we intentionally DO NOT call glutReshapeFunc() or implement reshape()

    // Create and initialize game after window & projection are set
    game = new GameManager(WIN_W, WIN_H);
    game->init();

    // Start home music safely (PlaySound-based SoundManager uses async mode)
    SoundManager::playHomeMusic();

    // Provide InputHandler with GameManager reference
    InputHandler::setGameManager(game);

    // Keyboard / mouse callbacks from your InputHandler adapter
    glutKeyboardFunc(InputHandler::keyboardDown);
    glutKeyboardUpFunc(InputHandler::keyboardUp);
    glutSpecialFunc(InputHandler::specialKey);
    glutMouseFunc(InputHandler::mouseClick);

    // Start fixed-timestep timer loop
    lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    glutTimerFunc(16, timerFunc, 0);

    // Enter main loop
    glutMainLoop();

    // Cleanup (unreachable with GLUT main loop, but keep for completeness)
    delete game;
    return 0;
}
