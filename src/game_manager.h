#pragma once
#include "home_screen.h"
#include "level_manager.h"
#include "bow.h"
#include "target.h"
#include "barrier.h"

enum GameState
{
    STATE_HOME,
    STATE_PLAYING,
    STATE_POPUP
};

class GameManager
{
private:
    int winW, winH;
    Bow *bow;
    Target *target;
    Barrier *barrier;
    LevelManager levelManager;
    HomeScreen homeScreen;

    int currentLevel;
    int attemptsLeft;
    int scoreThisLevel;
    int totalScore;

    float popupDelay;  // time remaining before popup appears
    bool pendingPopup; // waiting for delay before switching

    GameState state;
    bool showSuccessPopup;

    bool isPointInRect(int px, int py, float rx, float ry, float rw, float rh) const;

public:
    GameManager(int w, int h);
    ~GameManager();

    void init();
    void resize(int w, int h);

    void startLevel(int level);
    void resetLevel();

    void update(float dt);
    void render();

    void onKey(unsigned char key);
    void onSpecial(int key);
    void onMouse(int button, int stateBtn, int mx, int my);
};
