#include "Barrier.h"
#include <GL/glut.h>

Barrier::Barrier(float x_, float y_, float width_, float height_, bool moving)
    : x(x_), y(y_), width(width_), height(height_), moving(moving),
      speed(60.0f), active(true)
{
}

void Barrier::draw() {
    if (!active) return;

    glColor3f(0.45f, 0.45f, 0.45f);
    glBegin(GL_QUADS);
        glVertex2f(x - width * 0.5f, y - height * 0.5f);
        glVertex2f(x + width * 0.5f, y - height * 0.5f);
        glVertex2f(x + width * 0.5f, y + height * 0.5f);
        glVertex2f(x - width * 0.5f, y + height * 0.5f);
    glEnd();
}

void Barrier::update(double deltaTime) {
    if (!active || !moving) return;

    static bool movingUp = true;
    const float range = 60.0f;

    static float baseY = y;
    if (movingUp) {
        y += speed * (float)deltaTime;
        if (y > baseY + range) movingUp = false;
    } else {
        y -= speed * (float)deltaTime;
        if (y < baseY - range) movingUp = true;
    }
}

bool Barrier::checkCollision(float arrowX, float arrowY) {
    if (!active) return false;

    float left = x - width * 0.5f;
    float right = x + width * 0.5f;
    float bottom = y - height * 0.5f;
    float top = y + height * 0.5f;

    return (arrowX >= left && arrowX <= right && arrowY >= bottom && arrowY <= top);
}

void Barrier::setMoving(bool move, float moveSpeed) {
    moving = move;
    speed = moveSpeed;
}

void Barrier::deactivate() {
    active = false;
}
