#include "game_manager.h"
#include "ui_overlay.h"
#include <GL/glut.h>

void GameManager::render() {
    if (state == STATE_HOME) {
        homeScreen.draw();
        return;
    }

    glClearColor(0.52f, 0.8f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    float groundY = 10.0f;
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(0,0); glVertex2f(winW,0);
    glVertex2f(winW,groundY); glVertex2f(0,groundY);
    glEnd();

    if (barrier) barrier->draw();
    if (target) target->draw();
    if (bow) bow->draw();

    UIOverlay::drawHUD(totalScore, currentLevel, attemptsLeft, winW, winH);

    if (state == STATE_POPUP) UIOverlay::drawPopup(showSuccessPopup, scoreThisLevel, winW, winH);

    glutSwapBuffers();
}
