// FILE: src/arrow.cpp
#include "arrow.h"
#include "utils.h"

Arrow::Arrow(float x, float y)
    : posX(x), posY(y), velX(0), velY(0), gravity(-400.0f), flying(false), hit(false), hitAngle(0) {}

void Arrow::shoot(float angleDeg, float power)
{
    flying = true;
    hit = false;
    float rad = deg2rad(angleDeg);
    velX = power * std::cos(rad);
    velY = power * std::sin(rad);
}

void Arrow::update(float dt)
{
    if (!flying || hit) return;
    velY += gravity * dt;
    posX += velX * dt;
    posY += velY * dt;
    hitAngle = std::atan2(velY, velX) * 180.0f / 3.14159265358979323846f;

    // ground fallback
    if (posY < 0) {
        flying = false;
        hit = false;
    }
}

void Arrow::draw() const
{
    if (!flying && !hit) return;
    glPushMatrix();
    glTranslatef(posX, posY, 0);
    glRotatef(hitAngle, 0, 0, 1);

    glColor3f(0.55f, 0.27f, 0.07f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(-80, 0);
    glVertex2f(0, 0);
    glEnd();

    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(16, 0);
    glVertex2f(0, 6);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(16, 0);
    glVertex2f(0, -6);
    glEnd();

    glColor3f(0.2f, 0.6f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-80, 0);
    glVertex2f(-92, 7);
    glVertex2f(-70, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-80, 0);
    glVertex2f(-92, -7);
    glVertex2f(-70, 0);
    glEnd();

    glPopMatrix();
}

void Arrow::reset(float startX, float startY)
{
    posX = startX;
    posY = startY;
    velX = velY = 0;
    flying = false;
    hit = false;
    hitAngle = 0;
}

void Arrow::deactivate() { flying = false; }
bool Arrow::isActive() const { return flying || hit; }

bool Arrow::checkCollision(const Target &target)
{
    if (!flying || hit) return false;
    float dx = target.getX() - posX;
    float dy = target.getY() - posY;
    float dist = std::sqrt(dx*dx + dy*dy);
    if (dist <= target.getRadius()) {
        flying = false;
        hit = true;
        // nudge arrow into target slightly
        float norm = dist > 0 ? dist : 1.0f;
        posX += dx / norm * 10.0f;
        posY += dy / norm * 10.0f;
        hitAngle = std::atan2(velY, velX) * 180.0f / 3.14159265358979323846f;
        return true;
    }
    return false;
}
