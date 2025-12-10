#pragma once
#include <vector>
#include <GL/glut.h>

struct CircleButton {
    float x, y;
    float radius;
    int level;
};

class HomeScreen {
private:
    std::vector<CircleButton> levelButtons;
    int selectedLevel;
    int winW, winH;

    bool isPointInCircle(float px, float py, const CircleButton& circle) const;

public:
    HomeScreen(int windowWidth, int windowHeight);
    void draw() const;
    void mouseClick(int button, int state, int mx, int my);
    int getSelectedLevel() const { return selectedLevel; }

    // ✅ Added function to clear last selected level
    void resetSelectedLevel() { selectedLevel = -1; }
};
