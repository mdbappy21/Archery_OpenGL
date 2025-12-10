#include "game_manager.h"
#include "render_utils.h"
#include "ui_overlay.h"
#include <GL/glut.h>

void GameManager::render()
{
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (state == STATE_HOME) {
        homeScreen.draw();
        glutSwapBuffers();
        return;
    }

    if (state == STATE_PLAYING) {
        if (bow) bow->draw();
        if (target) target->draw();
        if (barrier) barrier->draw();

        UIOverlay::drawHUD(totalScore, currentLevel, attemptsLeft, winW, winH);

        glutSwapBuffers();
        return;
    }

    if (state == STATE_POPUP) {
        if (bow) bow->draw();
        if (target) target->draw();
        if (barrier) barrier->draw();

        UIOverlay::drawHUD(totalScore, currentLevel, attemptsLeft, winW, winH);
        UIOverlay::drawPopup(showSuccessPopup, scoreThisLevel, winW, winH);

        glutSwapBuffers();
        return;
    }

    // default swap to be safe
    glutSwapBuffers();
}
