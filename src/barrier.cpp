#include "barrier.h"
#include "render_utils.h"
#include <GL/glut.h>
#include <cmath>

Barrier::Barrier(float x_, float y_, float width_, float height_, bool moving_)
    : x(x_), y(y_), width(width_), height(height_), moving(moving_),
      speed(60.0f), active(true),
      rotateEnabled(false), rotateSpeed(0.0f), rotateAngle(0.0f),
      scalingEnabled(false), scaleFactor(1.0f), triggerScaleValue(1.0f), scaleTriggered(false),
      baseY(y_)
{
}

void Barrier::draw() const
{
    if (!active) return;

    // Center of rectangle
    float cx = x + width * 0.5f;
    float cy = y + height * 0.5f;

    glPushMatrix();

    // Apply transforms
    glTranslatef(cx, cy, 0.0f);
    glRotatef(rotateAngle, 0.0f, 0.0f, 1.0f);
    glScalef(scaleFactor, scaleFactor, 1.0f);
    glTranslatef(-cx, -cy, 0.0f);

    glColor3f(0.75f, 0.25f, 0.25f);
    glPointSize(2.0f);

    int x0 = static_cast<int>(x);
    int y0 = static_cast<int>(y);
    int x1 = static_cast<int>(x + width);
    int y1 = static_cast<int>(y + height);

    // Draw rectangle outline using Bresenham
    RenderUtils::drawLineBresenham(x0, y0, x1, y0); // bottom
    RenderUtils::drawLineBresenham(x1, y0, x1, y1); // right
    RenderUtils::drawLineBresenham(x1, y1, x0, y1); // top
    RenderUtils::drawLineBresenham(x0, y1, x0, y0); // left

    glPopMatrix();
}

void Barrier::update(float dt)
{
    if (rotateEnabled) {
        rotateAngle += rotateSpeed * dt;
        if (rotateAngle > 360.0f) rotateAngle -= 360.0f;
        else if (rotateAngle < -360.0f) rotateAngle += 360.0f;
    }

    if (scaleTriggered) {
        const float decaySpeed = 1.2f;
        scaleFactor -= decaySpeed * dt;
        if (scaleFactor <= 1.0f) {
            scaleFactor = 1.0f;
            scaleTriggered = false;
        }
    }

    if (!active || !moving)
        return;

    const float range = 60.0f;
    static bool movingUp = true;

    if (movingUp) {
        y += speed * dt;
        if (y > baseY + range) movingUp = false;
    } else {
        y -= speed * dt;
        if (y < baseY - range) movingUp = true;
    }
}

bool Barrier::checkCollision(float arrowX, float arrowY) const
{
    if (!active) return false;

    float left   = x;
    float right  = x + width;
    float bottom = y;
    float top    = y + height;

    return (arrowX >= left && arrowX <= right &&
            arrowY >= bottom && arrowY <= top);
}

void Barrier::setMoving(bool move, float moveSpeed)
{
    moving = move;
    speed = moveSpeed;
}

void Barrier::deactivate()
{
    active = false;
}

void Barrier::enableRotation(bool enable, float speed)
{
    rotateEnabled = enable;
    rotateSpeed = speed;
}

void Barrier::enableScaling(bool enable, float triggerScale)
{
    scalingEnabled = enable;
    triggerScaleValue = triggerScale;
    scaleFactor = 1.0f;
    scaleTriggered = false;
}

void Barrier::triggerScale()
{
    if (scalingEnabled) {
        scaleFactor = triggerScaleValue;
        scaleTriggered = true;
    }
}
