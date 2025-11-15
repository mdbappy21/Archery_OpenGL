#pragma once
#include <GL/glut.h>
#include <vector>
#include "arrow.h"

class Bow {
private:
    float x, y;
    float angle;
    float power;
    bool charging;
    std::vector<Arrow> arrows;

    const float maxPower = 1100.0f;
    const float bowHeight = 60.0f;
    const float bowWidth = 18.0f;

public:
    Bow(float startX, float startY);

    float gravity; // gravity for trajectory
    void setGravity(float g) { gravity = g; }

    void draw();
    void update(float dt);

    void aimUp();
    void aimDown();
    void increasePower();
    void decreasePower();
    void startCharge();
    void releaseCharge();

    void drawBowShape() const;
    void drawString() const;
    void drawTrajectory() const;
    void drawPowerIndicator() const;

    std::vector<Arrow>& getArrows() { return arrows; }
};
