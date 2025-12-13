#include "game_manager.h"
#include "sound_manager.h"
#include <GL/glut.h>

void GameManager::onKey(unsigned char key)
{
    if (key == 'q' || key == 'Q')
        exit(0);

    if (key == 'h' || key == 'H')
    {
        state = STATE_HOME;
        SoundManager::stopOverlayMusic();
        SoundManager::playHomeMusic();
        homeScreen.resetSelectedLevel();
        return;
    }

    if (state == STATE_HOME && key == ' ')
    {
        int lvl = homeScreen.getSelectedLevel();
        if (lvl > 0)
        {
            SoundManager::stopHomeMusic();
            startLevel(lvl);
        }
        return;
    }

    if (state == STATE_PLAYING)
    {
        if (!bow) return;

        switch (key)
        {
            case 'u': case 'U': bow->aimUp(); break;
            case 'd': case 'D': bow->aimDown(); break;

            case 'r': case 'R':
                bow->releaseCharge();

                if (barrier && currentLevelData.barrierScalingEnabled)
                    barrier->triggerScale();

                if (target && currentLevelData.targetReflectionEnabled)
                    target->reflect(winW);
                break;

            case ' ':
                bow->startCharge();
                break;
        }
    }
}

void GameManager::onSpecial(int key)
{
    if (state != STATE_PLAYING || !bow) return;

    if (key == GLUT_KEY_UP) bow->increasePower();
    if (key == GLUT_KEY_DOWN) bow->decreasePower();
}

void GameManager::onMouse(int button, int stateBtn, int mx, int my)
{
    if (state == STATE_HOME)
    {
        homeScreen.mouseClick(button, stateBtn, mx, my);
        int lvl = homeScreen.getSelectedLevel();
        if (lvl > 0)
        {
            SoundManager::stopHomeMusic();
            startLevel(lvl);
        }
        return;
    }

    if (state == STATE_POPUP &&
        button == GLUT_LEFT_BUTTON &&
        stateBtn == GLUT_DOWN)
    {
        float w = 470, h = 240;
        float cx = (winW - w) * 0.5f;
        float cy = (winH - h) * 0.5f;

        float btnW = 110, btnH = 38;
        float by = cy + 30;

        float bxHome = cx + 40;
        float bxRestart = bxHome + btnW + 30;
        float bxNext = bxRestart + btnW + 30;

        int py = winH - my;

        if (mx >= bxHome && mx <= bxHome + btnW && py >= by && py <= by + btnH)
        {
            SoundManager::stopOverlayMusic();
            state = STATE_HOME;
            SoundManager::playHomeMusic();
            homeScreen.resetSelectedLevel();
            return;
        }

        if (mx >= bxRestart && mx <= bxRestart + btnW && py >= by && py <= by + btnH)
        {
            SoundManager::stopOverlayMusic();
            resetLevel();
            return;
        }

        if (showSuccessPopup &&
            mx >= bxNext && mx <= bxNext + btnW &&
            py >= by && py <= by + btnH)
        {
            SoundManager::stopOverlayMusic();
            startLevel(currentLevel + 1);
            return;
        }
    }
}
