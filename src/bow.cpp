#include "bow.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Bow::Bow(float startX, float startY)
    : x(startX), y(startY), angle(45.0f), power(0.0f), charging(false),
      bowWidth(40.0f), bowHeight(120.0f), maxPower(1100.0f), gravity(-600.0f)
{}

void Bow::draw()
{
    // Draw bow shape
    drawBowShape();

    // Draw string
    drawString();

    // Draw charging arrow along the string
    if (charging)
    {
        float pullDist = -power / 8.0f;
        float arrowX = x + cos(angle * M_PI / 180.0f) * pullDist;
        float arrowY = y + bowHeight / 2.0f + sin(angle * M_PI / 180.0f) * pullDist;

        glPushMatrix();
        glTranslatef(arrowX, arrowY, 0);
        glRotatef(angle, 0, 0, 1);

        // Shaft
        glColor3f(0.5f, 0.25f, 0.1f);
        glLineWidth(4);
        glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(80, 0);
        glEnd();

        // Arrowhead
        glColor3f(0.8f, 0, 0);
        glBegin(GL_TRIANGLES);
        glVertex2f(85, 0);
        glVertex2f(70, 5);
        glVertex2f(70, -5);
        glEnd();

        // Fletching
        glColor3f(0.2f, 0.6f, 1.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(-10, 6);
        glVertex2f(10, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(-10, -6);
        glVertex2f(10, 0);
        glEnd();

        glPopMatrix();
    }

    // Draw all flying arrows using Arrow class
    for (auto &arrow : arrows)
        arrow.draw();

    // Trajectory preview if charging
    if (charging)
        drawTrajectory();

    // Power indicator
    if (charging)
        drawPowerIndicator();
}

void Bow::update(float dt)
{
    for (auto &arrow : arrows)
        arrow.update(dt);

    // Remove inactive arrows
    arrows.erase(
        std::remove_if(arrows.begin(), arrows.end(),
                       [](Arrow &a)
                       { return !a.isActive(); }),
        arrows.end());
}

// Controls
void Bow::aimUp()
{
    if (angle < 80.0f)
        angle += 2.0f;
}
void Bow::aimDown()
{
    if (angle > 10.0f)
        angle -= 2.0f;
}
void Bow::increasePower() { power = std::min(power + 20.0f, maxPower); }
void Bow::decreasePower() { power = std::max(power - 20.0f, 0.0f); }
void Bow::startCharge()
{
    charging = true;
    power = 0.0f;
}

// Release arrow using Arrow class (Bow only handles its own state)
void Bow::releaseCharge()
{
    if (!charging)
        return;
    charging = false;

    float pullDist = -power / 8.0f;
    float arrowX = x + cos(angle * M_PI / 180.0f) * pullDist;
    float arrowY = y + bowHeight / 2.0f + sin(angle * M_PI / 180.0f) * pullDist;

    Arrow newArrow(arrowX, arrowY);
    newArrow.shoot(angle, power);
    arrows.push_back(newArrow);

    std::cout << "Arrow fired: power=" << power << "\n";
    power = 0.0f;
}

// Drawing helpers
void Bow::drawBowShape() const
{
    glColor3f(0.5f, 0.2f, 0);
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    int segments = 20;
    for (int i = 0; i <= segments; i++)
    {
        float t = (float)i / segments;
        glVertex2f(x + sin(t * M_PI) * bowWidth, y + t * bowHeight);
    }
    glEnd();
}

void Bow::drawString() const
{
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2);
    glBegin(GL_LINES);

    float topX = x + sin(M_PI) * bowWidth;
    float topY = y + bowHeight;
    float bottomX = x + sin(0) * bowWidth;
    float bottomY = y;

    float pullDist = charging ? -power / 8.0f : 0.0f;
    float arrowX = x + cos(angle * M_PI / 180.0f) * pullDist;
    float arrowY = y + bowHeight / 2.0f + sin(angle * M_PI / 180.0f) * pullDist;

    glVertex2f(topX, topY);
    glVertex2f(arrowX, arrowY);
    glVertex2f(arrowX, arrowY);
    glVertex2f(bottomX, bottomY);

    glEnd();
}

void Bow::drawTrajectory() const
{
    glColor3f(1, 0, 0);
    glPointSize(3);
    glBegin(GL_POINTS);

    float simX = x + cos(angle * M_PI / 180.0f) * power / 8.0f;
    float simY = y + bowHeight / 2.0f + sin(angle * M_PI / 180.0f) * power / 8.0f;
    float vX = power * cos(angle * M_PI / 180.0f);
    float vY = power * sin(angle * M_PI / 180.0f);
    float g = gravity;
    float dt = 0.05f;

    for (int i = 0; i < 100; i++)
    {
        glVertex2f(simX, simY);
        vY += g * dt;
        simX += vX * dt;
        simY += vY * dt;
        if (simY < 0)
            break;
    }

    glEnd();
}

void Bow::drawPowerIndicator() const
{
    float w = 100, h = 10;
    float filled = (power / maxPower) * w;

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(x, y - 20);
    glVertex2f(x + w, y - 20);
    glVertex2f(x + w, y - 10);
    glVertex2f(x, y - 10);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex2f(x, y - 20);
    glVertex2f(x + filled, y - 20);
    glVertex2f(x + filled, y - 10);
    glVertex2f(x, y - 10);
    glEnd();
}
