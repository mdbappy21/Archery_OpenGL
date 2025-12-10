// FILE: src/render_utils.h
#pragma once
#include <string>
#include <GL/glut.h>
#include <cmath>

namespace RenderUtils {

// Draw text at world coordinates (uses GLUT bitmap font)
inline void drawText(float x, float y, const std::string &text) {
    glRasterPos2f(x, y);
    for (char c : text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// Draw a filled circle (triangle fan)
inline void drawFilledCircle(float cx, float cy, float r, int segments = 32) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float a = (2.0f * 3.14159265358979323846f * i) / segments;
        glVertex2f(cx + cosf(a) * r, cy + sinf(a) * r);
    }
    glEnd();
}

// Draw an outline circle
inline void drawCircleOutline(float cx, float cy, float r, int segments = 32) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float a = (2.0f * 3.14159265358979323846f * i) / segments;
        glVertex2f(cx + cosf(a) * r, cy + sinf(a) * r);
    }
    glEnd();
}

// Draw a smooth curved path between two points (quadratic bezier-ish)
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

} // namespace RenderUtils
