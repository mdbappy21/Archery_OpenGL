#ifndef BARRIER_H
#define BARRIER_H

class Barrier
{
private:
    float x;
    float y;
    float width;
    float height;

    bool moving;
    float speed;
    bool active;

    // rotation
    bool rotateEnabled;
    float rotateSpeed;
    float rotateAngle;

    // scaling
    bool scalingEnabled;
    float scaleFactor;
    float triggerScaleValue;
    bool scaleTriggered;

    // movement base (for oscillation)
    float baseY;

public:
    Barrier(float x, float y, float width, float height, bool moving = false);

    // lifecycle
    void update(float dt);
    void draw() const;
    bool checkCollision(float arrowX, float arrowY) const;

    // movement control
    void setMoving(bool move, float moveSpeed = 60.0f);

    // enable/trigger transforms
    void enableRotation(bool enable, float speed);
    void enableScaling(bool enable, float triggerScale);
    void triggerScale();

    void deactivate();
    bool isActive() const { return active; }
};

#endif // BARRIER_H
