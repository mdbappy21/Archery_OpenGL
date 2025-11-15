#pragma once
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "target.h"

class Arrow {
public:
    Arrow(float x = 0, float y = 0);

    void shoot(float angleDeg, float power);
    void update(float dt);
    void draw() const;

    void reset(float startX, float startY);
    void deactivate();
    bool isActive() const;

    bool checkCollision(const Target &target);
    void setHit(bool v) { hit = v; }
    bool hasHit() const { return hit; }

    float getX() const { return posX; }
    float getY() const { return posY; }

private:
    float posX, posY;
    float velX, velY;
    float gravity;
    bool flying;
    bool hit;
    float hitAngle;
};
