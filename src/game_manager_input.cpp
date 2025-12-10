#include "game_manager.h"
#include <GL/glut.h>

void GameManager::onKey(unsigned char key) {
    if (state == STATE_HOME) {
        if (key == 27) exit(0);
        if (key == 'p' || key == 'P') {
            int lvl = homeScreen.getSelectedLevel();
            if (lvl < 0) lvl = 1;
            startLevel(lvl);
        }
        return;
    }

    if (!bow) return;

    if (state == STATE_POPUP) {
        if (key == 'q' || key == 'Q') exit(0);
        if (key == 'h' || key == 'H') {
            state = STATE_HOME;
            homeScreen.resetSelectedLevel();
            glutPostRedisplay();
        }
        if (key == 'r' || key == 'R') resetLevel();
        return;
    }

    switch (key) {
        case ' ': bow->startCharge(); break;
        case 'r': case 'R': bow->releaseCharge(); break;
        case 'u': case 'U': bow->aimUp(); break;
        case 'd': case 'D': bow->aimDown(); break;
        case 'q': case 'Q': exit(0); break;
        case 'h': case 'H': state = STATE_HOME; homeScreen.resetSelectedLevel(); glutPostRedisplay(); break;
    }
}

void GameManager::onSpecial(int key) {
    if (!bow || state != STATE_PLAYING) return;
    if (key == GLUT_KEY_UP) bow->increasePower();
    if (key == GLUT_KEY_DOWN) bow->decreasePower();
    if (key == GLUT_KEY_RIGHT) bow->aimUp();
    if (key == GLUT_KEY_LEFT) bow->aimDown();
}

void GameManager::onMouse(int button, int stateBtn, int mx, int my) {
    int py = winH - my;

    if (state == STATE_HOME) {
        homeScreen.mouseClick(button, stateBtn, mx, my);
        int lvl = homeScreen.getSelectedLevel();
        if (lvl > 0) startLevel(lvl);
        return;
    }

    if (state == STATE_POPUP && button == GLUT_LEFT_BUTTON && stateBtn == GLUT_DOWN) {
        float w=400, h=200, cx=(winW-w)/2.0f, cy=(winH-h)/2.0f;
        float btnW=100, btnH=36, by=cy+30;
        float bxHome=cx+40, bxRestart=bxHome+btnW+30, bxNext=bxRestart+btnW+30;

        if (isPointInRect(mx, py, bxHome, by, btnW, btnH)) {
            state = STATE_HOME;
            delete bow; bow=nullptr;
            delete target; target=nullptr;
            delete barrier; barrier=nullptr;
            homeScreen.resetSelectedLevel();

            // Schedule redraw instead of manual draw
            glutPostRedisplay();
            return;
        }

        if (isPointInRect(mx, py, bxRestart, by, btnW, btnH)) {
            resetLevel();
            glutPostRedisplay();
            return;
        }

        if (showSuccessPopup && isPointInRect(mx, py, bxNext, by, btnW, btnH)) {
            if (currentLevel < 20) startLevel(currentLevel+1);
            else {
                state = STATE_HOME;
                homeScreen.resetSelectedLevel();
            }
            glutPostRedisplay();
            return;
        }
    }
}

