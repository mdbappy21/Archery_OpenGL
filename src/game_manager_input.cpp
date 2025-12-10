#include "game_manager.h"
#include "sound_manager.h"
#include "ui_overlay.h"
#include <GL/glut.h>
#include <iostream>

void GameManager::onKey(unsigned char key)
{
    if (key == 'q' || key == 'Q') {
        exit(0);
    }

    if (key == 'h' || key == 'H') {
        state = STATE_HOME;
        SoundManager::stopOverlayMusic();
        SoundManager::playHomeMusic();
        homeScreen.resetSelectedLevel();
        return;
    }

    if (state == STATE_HOME && (key == ' ')) {
        int lvl = homeScreen.getSelectedLevel();
        if (lvl > 0) {
            SoundManager::stopHomeMusic();
            startLevel(lvl);
        }
        return;
    }

    if (state == STATE_PLAYING) {
        if (!bow) return;
        switch (key) {
            case 'u': case 'U': bow->aimUp(); break;
            case 'd': case 'D': bow->aimDown(); break;
            case 'r': case 'R': bow->releaseCharge(); break;
            case ' ': // space could start charge
                bow->startCharge();
                break;
            default: break;
        }
    }
}

void GameManager::onSpecial(int key)
{
    if (state != STATE_PLAYING || !bow) return;

    switch (key) {
        case GLUT_KEY_UP: bow->increasePower(); break;
        case GLUT_KEY_DOWN: bow->decreasePower(); break;
        default: break;
    }
}

void GameManager::onMouse(int button, int stateMouse, int mx, int my)
{
    if (state == STATE_HOME) {
    homeScreen.mouseClick(button, stateMouse, mx, my);

    int lvl = homeScreen.getSelectedLevel();
    if (lvl > 0) {
        SoundManager::stopHomeMusic();
        startLevel(lvl);
    }
    return;
}


    if (state == STATE_POPUP && button == GLUT_LEFT_BUTTON && stateMouse == GLUT_DOWN) {
        float w = 470, h = 240;
        float cx = (winW - w) / 2.0f;
        float cy = (winH - h) / 2.0f;

        float btnW = 110, btnH = 38;
        float by = cy + 30;
        float bxHome = cx + 40;
        float bxRestart = bxHome + btnW + 30;
        float bxNext = bxRestart + btnW + 30;

        int py = winH - my;

        if (mx >= bxHome && mx <= bxHome + btnW && py >= by && py <= by + btnH) {
            SoundManager::stopOverlayMusic();
            state = STATE_HOME;
            SoundManager::playHomeMusic();
            homeScreen.resetSelectedLevel();
            return;
        }

        if (mx >= bxRestart && mx <= bxRestart + btnW && py >= by && py <= by + btnH) {
            SoundManager::stopOverlayMusic();
            resetLevel();
            return;
        }

        if (showSuccessPopup &&
            mx >= bxNext && mx <= bxNext + btnW &&
            py >= by && py <= by + btnH) {
            SoundManager::stopOverlayMusic();
            startLevel(currentLevel + 1);
            return;
        }
    }
}
