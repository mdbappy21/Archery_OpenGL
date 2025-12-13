// FILE: src/render_utils.h
#pragma once
#include <string>
#include <GL/glut.h>
#include <cmath>

namespace RenderUtils {

// ================= TEXT =================
inline void drawText(float x, float y, const std::string &text) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// ================= CIRCLES (OpenGL) =================
inline void drawFilledCircle(float cx, float cy, float r, int segments = 32) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float a = (2.0f * 3.14159265358979323846f * i) / segments;
        glVertex2f(cx + cosf(a) * r, cy + sinf(a) * r);
    }
    glEnd();
}

inline void drawCircleOutline(float cx, float cy, float r, int segments = 32) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float a = (2.0f * 3.14159265358979323846f * i) / segments;
        glVertex2f(cx + cosf(a) * r, cy + sinf(a) * r);
    }
    glEnd();
}

// ================= PATH =================
inline void drawCurvedPath(float x1, float y1, float x2, float y2, float curveStrength = 0.25f) {
    float midX = (x1 + x2) / 2.0f;
    float midY = (y1 + y2) / 2.0f + (y2 > y1 ? 20.0f : -20.0f) * curveStrength;

    glBegin(GL_LINE_STRIP);
    for (float t = 0.0f; t <= 1.001f; t += 0.02f) {
        float x = (1 - t) * (1 - t) * x1 + 2 * (1 - t) * t * midX + t * t * x2;
        float y = (1 - t) * (1 - t) * y1 + 2 * (1 - t) * t * midY + t * t * y2;
        glVertex2f(x, y);
    }
    glEnd();
}

// ================= RECTANGLES =================
inline void drawFilledRect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
    glVertex2f(x,     y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x,     y + h);
    glEnd();
}

inline void drawRectOutline(float x, float y, float w, float h) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(x,     y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x,     y + h);
    glEnd();
}

// ================= ALGORITHMIC DRAWING =================

// Bresenham line
void drawLineBresenham(int x0, int y0, int x1, int y1);

// Midpoint circle
void drawCircleMidpoint(int cx, int cy, int radius);

} // namespace RenderUtils
