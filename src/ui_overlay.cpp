#include "ui_overlay.h"
#include "render_utils.h"
#include <GL/glut.h>
#include <string>
#include <iostream>

namespace UIOverlay {

void drawHUD(int totalScore, int currentLevel, int attemptsLeft, int winW, int winH) {
    glColor3f(0, 0, 0);
    RenderUtils::drawText(10, winH - 30, "Score: " + std::to_string(totalScore));
    RenderUtils::drawText(10, winH - 60, "Level: " + std::to_string(currentLevel));
    RenderUtils::drawText(10, winH - 90, "Attempts left: " + std::to_string(attemptsLeft));
}

void drawPopup(bool success, int scoreThisLevel, int winW, int winH) {
    float w = 470, h = 240;
    float cx = (winW - w) / 2.0f;
    float cy = (winH - h) / 2.0f;

    // Dimmed translucent background
    glColor4f(0, 0, 0, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0); glVertex2f(winW, 0);
    glVertex2f(winW, winH); glVertex2f(0, winH);
    glEnd();

    // Popup shadow
    glColor4f(0, 0, 0, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(cx + 6, cy - 6);
    glVertex2f(cx + w + 6, cy - 6);
    glVertex2f(cx + w + 6, cy + h - 6);
    glVertex2f(cx + 6, cy + h - 6);
    glEnd();

    // Popup background (white)
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(cx, cy);
    glVertex2f(cx + w, cy);
    glVertex2f(cx + w, cy + h);
    glVertex2f(cx, cy + h);
    glEnd();

    // Header gradient
    glBegin(GL_QUADS);
    if (success) {
        glColor3f(0.2f, 0.8f, 0.3f); // bright green top
        glVertex2f(cx, cy + h - 50);
        glVertex2f(cx + w, cy + h - 50);
        glColor3f(0.1f, 0.6f, 0.2f); // darker bottom
        glVertex2f(cx + w, cy + h);
        glVertex2f(cx, cy + h);
    } else {
        glColor3f(0.9f, 0.3f, 0.3f);
        glVertex2f(cx, cy + h - 50);
        glVertex2f(cx + w, cy + h - 50);
        glColor3f(0.6f, 0.1f, 0.1f);
        glVertex2f(cx + w, cy + h);
        glVertex2f(cx, cy + h);
    }
    glEnd();

    // Title text
    glColor3f(1, 1, 1);
    std::string title = success ? "LEVEL COMPLETE!" : "LEVEL FAILED!";
    RenderUtils::drawText(cx + (w / 2) - (title.size() * 4), cy + h - 30, title);

    // Score display (only if success)
    if (success) {
        glColor3f(0, 0, 0);
        std::string scoreText = "Score this level: " + std::to_string(scoreThisLevel);
        RenderUtils::drawText(cx + (w / 2) - (scoreText.size() * 4), cy + h - 80, scoreText);
    }

    // Buttons setup
    float btnW = 110, btnH = 38;
    float by = cy + 30;
    float bxHome = cx + 40;
    float bxRestart = bxHome + btnW + 30;
    float bxNext = bxRestart + btnW + 30;

    // Helper for 3D-style button
    auto drawButton = [&](float x, float y, const std::string& label) {
        // Button background (top light to bottom dark)
        glBegin(GL_QUADS);
        glColor3f(0.9f, 0.9f, 0.9f);
        glVertex2f(x, y + btnH);
        glVertex2f(x + btnW, y + btnH);
        glColor3f(0.7f, 0.7f, 0.7f);
        glVertex2f(x + btnW, y);
        glVertex2f(x, y);
        glEnd();

        // Border
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y); glVertex2f(x + btnW, y);
        glVertex2f(x + btnW, y + btnH); glVertex2f(x, y + btnH);
        glEnd();

        // Label text (centered)
        glColor3f(0, 0, 0);
        RenderUtils::drawText(x + btnW / 2 - (label.size() * 3), y + btnH / 2 - 6, label);
    };

    // Buttons
    drawButton(bxHome, by, "Home");
    drawButton(bxRestart, by, "Restart");
    if (success) drawButton(bxNext, by, "Next");
}

} // namespace UIOverlay
