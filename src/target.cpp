#include "target.h"

Target::Target(float tx, float ty, float r, bool move, float spd)
 : x(tx), y(ty), radius(r), moving(move), speed(spd), direction(1.0f) {}


void Target::update(float dt)
{
    if (moving) {
        x += speed * direction * dt;
        if (x > 750 || x < 550) direction *= -1.0f;
    }
}

void Target::draw() const {
    int segments = 64;

    glColor3f(1.0f, 1.0f, 1.0f); // white
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; ++i) {
        float ang = i * 2.0f * 3.14159f / segments;
        glVertex2f(x + std::cos(ang) * radius, y + std::sin(ang) * radius);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; ++i) {
        float ang = i * 2.0f * 3.14159f / segments;
        glVertex2f(x + std::cos(ang) * radius*0.80f, y + std::sin(ang) * radius * 0.80f);
    }
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; ++i) {
        float ang = i * 2.0f * 3.14159f / segments;
        glVertex2f(x + std::cos(ang) * radius*0.60f, y + std::sin(ang) * radius * 0.60f);
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; ++i) {
        float ang = i * 2.0f * 3.14159f / segments;
        glVertex2f(x + std::cos(ang) * radius * 0.40f, y + std::sin(ang) * radius * 0.40f);
    }
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f); // yellow
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; ++i) {
        float ang = i * 2.0f * 3.14159f / segments;
        glVertex2f(x + std::cos(ang) * radius * 0.20f, y + std::sin(ang) * radius * 0.20f);
    }
    glEnd();
}

int Target::checkHit(float ax, float ay) const
{
    float dx = ax - x;
    float dy = ay - y;
    float dist = std::sqrt(dx*dx + dy*dy);
    if (dist <= radius * 0.2f) return 10;
    if (dist <= radius * 0.5f) return 7;
    if (dist <= radius) return 5;
    return 0;
}

void Target::reflect(int screenW) {
    x = screenW - x;
}