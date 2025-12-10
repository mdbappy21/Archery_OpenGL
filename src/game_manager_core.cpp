#include "game_manager.h"
#include "ui_overlay.h"
#include <GL/glut.h>
#include <algorithm>

GameManager::GameManager(int w, int h)
    : winW(w), winH(h), bow(nullptr), target(nullptr), barrier(nullptr),
      levelManager(), homeScreen(w,h), currentLevel(1),
      attemptsLeft(3), scoreThisLevel(0), totalScore(0),
      state(STATE_HOME), showSuccessPopup(false)
{}

GameManager::~GameManager() {
    delete bow; delete target; delete barrier;
}

void GameManager::init() {
    levelManager.loadAll();
}

void GameManager::resize(int w, int h) {
    winW = w; winH = h;
}

void GameManager::startLevel(int level) {
    currentLevel = level;
    attemptsLeft = 3;
    scoreThisLevel = 0;

    delete bow; bow = nullptr;
    delete target; target = nullptr;
    delete barrier; barrier = nullptr;

    const LevelData &ld = levelManager.getLevel(level);
    bow = new Bow(120.0f, 160.0f);
    bow->setGravity(ld.gravity);
    target = new Target(ld.targetX, ld.targetY, ld.targetRadius,
                        ld.targetMoving, ld.targetMoving ? ld.targetMoveSpeed : 0.0f);

    if (ld.barrierExists) {
        barrier = new Barrier(ld.barrierX, ld.barrierY, ld.barrierW, ld.barrierH);
        if (ld.barrierMoving) barrier->setMoving(true, ld.barrierMoveSpeed);
    }

    state = STATE_PLAYING;
    glutPostRedisplay(); // ensure UI updates immediately
}

void GameManager::resetLevel() { startLevel(currentLevel); }

bool GameManager::isPointInRect(int px,int py,float rx,float ry,float rw,float rh) const {
    return px >= rx && px <= rx + rw && py >= ry && py <= ry + rh;
}

void GameManager::update(float dt) {
    if (state != STATE_PLAYING) return;

    if (bow) bow->update(dt);
    if (target) target->update(dt);
    if (barrier) barrier->update(dt);

    float groundY = 10.0f;

    if (bow) {
        for (auto &a : bow->getArrows()) {
            if (!a.hasHit()) {
                if (barrier && barrier->checkCollision(a.getX(), a.getY())) {
                    a.setHit(true);
                    attemptsLeft = std::max(0, attemptsLeft - 1);
                }
                else if (target && a.checkCollision(*target)) {
                    int s = target->checkHit(a.getX(), a.getY());
                    scoreThisLevel = s;
                    totalScore += s;
                    state = STATE_POPUP;
                    showSuccessPopup = true;
                }
                else if (a.getY() <= groundY || a.getX() < 0 || a.getX() > winW) {
                    a.setHit(true);
                    attemptsLeft = std::max(0, attemptsLeft - 1);
                }
            }
        }
    }

    if (attemptsLeft <= 0 && state == STATE_PLAYING) {
        state = STATE_POPUP;
        showSuccessPopup = false;
        scoreThisLevel = 0;
    }
}
