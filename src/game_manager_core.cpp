#include "game_manager.h"
#include "sound_manager.h"
#include "ui_overlay.h"
#include <GL/glut.h>
#include <iostream>

GameManager::GameManager(int w, int h)
    : winW(w), winH(h), bow(nullptr), target(nullptr), barrier(nullptr),
      homeScreen(w, h), currentLevel(1),
      attemptsLeft(3), scoreThisLevel(0), totalScore(0),
      popupDelay(0.0f), pendingPopup(false),
      state(STATE_HOME), showSuccessPopup(false)
{
}

GameManager::~GameManager()
{
    delete bow;
    delete target;
    delete barrier;
}

void GameManager::init()
{
    levelManager.loadAll();
    state = STATE_HOME;
    glutPostRedisplay();
}

void GameManager::resize(int w, int h)
{
    winW = w;
    winH = h;
}

void GameManager::startLevel(int level)
{
    SoundManager::stopHomeMusic();
    SoundManager::stopOverlayMusic();

    currentLevel = level;
    attemptsLeft = 3;
    scoreThisLevel = 0;

    delete bow; bow = nullptr;
    delete target; target = nullptr;
    delete barrier; barrier = nullptr;

    const LevelData &ld = levelManager.getLevel(level);
    currentLevelData = ld;

    bow = new Bow(120.0f, 160.0f);
    bow->setGravity(ld.gravity);

    target = new Target(ld.targetX, ld.targetY, ld.targetRadius,
                        ld.targetMoving != 0,
                        ld.targetMoving ? ld.targetMoveSpeed : 0.0f);

    if (ld.barrierExists)
    {
        barrier = new Barrier(ld.barrierX, ld.barrierY, ld.barrierW, ld.barrierH, ld.barrierMoving != 0);

        if (ld.barrierMoving)
            barrier->setMoving(true, ld.barrierMoveSpeed);

        if (ld.barrierRotateEnabled)
            barrier->enableRotation(true, ld.barrierRotateSpeed);

        if (ld.barrierScalingEnabled)
            barrier->enableScaling(true, ld.barrierScaleOnTrigger);
    }

    state = STATE_PLAYING;
    glutPostRedisplay();
}

void GameManager::resetLevel()
{
    SoundManager::stopOverlayMusic();
    startLevel(currentLevel);
}

bool GameManager::isPointInRect(int px, int py, float rx, float ry, float rw, float rh) const
{
    return px >= rx && px <= rx + rw && py >= ry && py <= ry + rh;
}

void GameManager::update(float dt)
{
    if (state != STATE_PLAYING)
        return;

    if (bow) bow->update(dt);
    if (target) target->update(dt);
    if (barrier) barrier->update(dt);

    float groundY = 10.0f;

    for (auto &a : bow->getArrows())
    {
        if (!a.hasHit())
        {
            if (barrier && barrier->checkCollision(a.getX(), a.getY()))
            {
                a.setHit(true);
                SoundManager::playMissSound();
                attemptsLeft = std::max(0, attemptsLeft - 1);
                continue;
            }

            if (target && a.checkCollision(*target))
            {
                int s = target->checkHit(a.getX(), a.getY());
                scoreThisLevel = s;
                totalScore += s;

                SoundManager::playHitSound();

                pendingPopup = true;
                popupDelay = 0.8f;
                showSuccessPopup = true;

                a.setHit(true);
                continue;
            }

            if (a.getY() <= groundY || a.getX() < 0 || a.getX() > winW)
            {
                a.setHit(true);
                SoundManager::playMissSound();
                attemptsLeft = std::max(0, attemptsLeft - 1);
            }
        }
    }

    if (attemptsLeft <= 0 && state == STATE_PLAYING)
    {
        SoundManager::playMissSound();
        SoundManager::playOverlayMusic();
        state = STATE_POPUP;
        showSuccessPopup = false;
        scoreThisLevel = 0;
        return;
    }

    if (pendingPopup)
    {
        popupDelay -= dt;
        if (popupDelay <= 0.0f)
        {
            pendingPopup = false;
            state = STATE_POPUP;
            SoundManager::playOverlayMusic();
        }
    }
}
