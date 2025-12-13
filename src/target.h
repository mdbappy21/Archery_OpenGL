#pragma once
#include <GL/glut.h>
#include <cmath>

class Target {
private:
    float x, y, radius;
    bool moving;
    float speed;
    float direction;
public:
    Target(float tx = 650, float ty = 250, float r = 50, bool move = false, float spd = 0.0f);
    void update(float dt);
    void draw() const;
    int checkHit(float ax, float ay) const;
    bool isMoving() const { return moving; }
    float getX() const { return x; }
    float getY() const { return y; }
    float getRadius() const { return radius; }
    void setMoving(bool m) { moving = m; }
    void setPosition(float nx, float ny) { x = nx; y = ny; }
    void reflect(int screenW);
};
