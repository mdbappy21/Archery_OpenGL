// FILE: src/home_screen.cpp
#include "home_screen.h"
#include "render_utils.h"
#include <algorithm>
#include <string>
#include <iostream>

HomeScreen::HomeScreen(int windowWidth, int windowHeight)
    : selectedLevel(-1), winW(windowWidth), winH(windowHeight)
{
    float radius = 30.0f;
    float spacingX = 100.0f;
    float spacingY = 80.0f;
    float startX = 120.0f;
    float startY = winH - 130.0f;

    // create layout similar to your design
    for (int i = 0; i < 4; ++i) levelButtons.push_back({startX + i * spacingX, startY, radius, i + 1});
    for (int i = 0; i < 4; ++i) levelButtons.push_back({startX + i * spacingX, startY - spacingY, radius, 8 - i});
    for (int i = 0; i < 4; ++i) levelButtons.push_back({startX + i * spacingX, startY - 2 * spacingY, radius, 9 + i});
    for (int i = 0; i < 4; ++i) levelButtons.push_back({startX + i * spacingX, startY - 3 * spacingY, radius, 16 - i});
    for (int i = 0; i < 4; ++i) levelButtons.push_back({startX + i * spacingX, startY - 4 * spacingY, radius, 17 + i});
}

bool HomeScreen::isPointInCircle(float px, float py, const CircleButton& circle) const {
    float dx = px - circle.x;
    float dy = py - circle.y;
    return dx*dx + dy*dy <= circle.radius * circle.radius;
}

void HomeScreen::draw() const {
    glClearColor(0.52f, 0.8f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Title
    glColor3f(0,0,0);
    std::string title = "Welcome to Archery Game 2026";
    RenderUtils::drawText(winW/2 - (int)title.size()*4, winH - 30, title);

    // Subtitle
    std::string sub = "Select Level";
    RenderUtils::drawText(winW/2 - (int)sub.size()*4 - 60, winH - 70, sub);

    // glowing curved paths
    std::vector<CircleButton> sorted = levelButtons;
    std::sort(sorted.begin(), sorted.end(), [](const CircleButton &a, const CircleButton &b){ return a.level < b.level; });

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int glow = 3; glow >= 0; --glow) {
        float alpha = 0.12f * glow + 0.05f;
        glLineWidth(6 + glow*2);
        glColor4f(1.0f, 0.5f, 0.1f, alpha);
        for (size_t i = 0; i + 1 < sorted.size(); ++i) {
            RenderUtils::drawCurvedPath(sorted[i].x, sorted[i].y, sorted[i+1].x, sorted[i+1].y);
        }
    }
    glDisable(GL_BLEND);

    // buttons
    for (const auto &btn : levelButtons) {
        glColor3f(0.9f, 0.5f, 0.1f);
        RenderUtils::drawFilledCircle(btn.x, btn.y, btn.radius, 48);
        glColor3f(0,0,0);
        RenderUtils::drawCircleOutline(btn.x, btn.y, btn.radius, 48);

        std::string num = std::to_string(btn.level);
        RenderUtils::drawText(btn.x - 6, btn.y - 6, num);
    }

    // Controls box
    float panelX = winW - 260, panelY = winH - 100;
    std::vector<std::string> controls = {
        "Control modes :",
        "Space      : Start Game",
        "R/r            : Release Arrow",
        "U/u           : Aim Up",
        "D/d           : Aim Down",
        "Up key     : Power increase",
        "Down key : Power decrease",
        "H/h           : Back to Home",
        "Q/q           : Quit Playing"
    };
    glColor3f(0,0,0);
    for (size_t i=0;i<controls.size();++i) RenderUtils::drawText(panelX, panelY - i*24, controls[i]);

    glutSwapBuffers();
}

void HomeScreen::mouseClick(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int py = winH - my; // convert window y to world y
        for (const auto &btn : levelButtons) {
            if (isPointInCircle(mx, py, btn)) {
                selectedLevel = btn.level;
                std::cout << "HomeScreen: selected level " << selectedLevel << std::endl;
            }
        }
    }
}
