#pragma once
#include <string>

namespace UIOverlay {

// Draws the in-game HUD (score, level, attempts).
void drawHUD(int totalScore, int currentLevel, int attemptsLeft, int winW, int winH);

// Draws a popup alert box after level completion or failure.
void drawPopup(bool success, int scoreThisLevel, int winW, int winH);

} // namespace UIOverlay
