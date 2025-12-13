#include "game_manager.h"
#include "ui_overlay.h"
#include <GL/glut.h>

void GameManager::render()
{
    glClearColor(0.9f, 0.9f, 0.9f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (state == STATE_HOME)
    {
        homeScreen.draw();
        glutSwapBuffers();
        return;
    }

    if (state == STATE_PLAYING)
    {
        if (barrier) barrier->draw();
        if (target) target->draw();
        if (bow)    bow->draw();

        UIOverlay::drawHUD(totalScore, currentLevel, attemptsLeft, winW, winH);
        glutSwapBuffers();
        return;
    }

    if (state == STATE_POPUP)
    {
        if (barrier) barrier->draw();
        if (target) target->draw();
        if (bow)    bow->draw();

        UIOverlay::drawHUD(totalScore, currentLevel, attemptsLeft, winW, winH);
        UIOverlay::drawPopup(showSuccessPopup, scoreThisLevel, winW, winH);

        glutSwapBuffers();
        return;
    }

    glutSwapBuffers();
}
