// FILE: src/input_handler.cpp
#include "input_handler.h"
#include "game_manager.h" // need GameManager declaration
#include <iostream>

static GameManager* g_game = nullptr;

namespace InputHandler {

void setGameManager(GameManager* gm) {
    g_game = gm;
}

void keyboardDown(unsigned char key, int x, int y) {
    (void)x; (void)y;
    if (!g_game) return;
    g_game->onKey(key);
}

void keyboardUp(unsigned char key, int x, int y) {
    (void)key; (void)x; (void)y;
    // nothing for now, can be extended
}

void specialKey(int key, int x, int y) {
    (void)x; (void)y;
    if (!g_game) return;
    g_game->onSpecial(key);
}

void mouseClick(int button, int state, int x, int y) {
    if (!g_game) return;
    g_game->onMouse(button, state, x, y);
}

} // namespace InputHandler
