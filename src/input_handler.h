// FILE: src/input_handler.h
#pragma once
#include <GL/glut.h>

// Forward
class GameManager;

namespace InputHandler {
    void setGameManager(GameManager* gm);
    void keyboardDown(unsigned char key, int x, int y);
    void keyboardUp(unsigned char key, int x, int y);
    void specialKey(int key, int x, int y);
    void mouseClick(int button, int state, int x, int y);
}
