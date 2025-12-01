#ifndef BARRIER_H
#define BARRIER_H

class Barrier {
private:
    float x, y;
    float width, height;
    bool moving;
    float speed;
    bool active;

public:
    Barrier(float x, float y, float width, float height, bool moving = false);

    void draw();
    void update(double deltaTime);
    bool checkCollision(float arrowX, float arrowY);

    void setMoving(bool move, float moveSpeed = 60.0f);

    void deactivate();

    bool isActive() const { return active; }
};

#endif
