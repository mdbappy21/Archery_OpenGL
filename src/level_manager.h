#pragma once
#include <vector>
#include <string>

struct LevelData {
    int levelNumber;
    float targetX;
    float targetY;
    float targetRadius;
    int targetMoving;
    float targetMoveSpeed;
    int targetReflectionEnabled;

    int barrierExists;
    float barrierX;
    float barrierY;
    float barrierW;
    float barrierH;
    int barrierMoving;
    float barrierMoveSpeed;

    int barrierRotateEnabled;
    float barrierRotateSpeed;

    int barrierScalingEnabled;
    float barrierScaleOnTrigger;

    float gravity;
};

class LevelManager {
private:
    std::vector<LevelData> levels;
public:
    LevelManager() = default;
    void loadAll();              // load all levels from files
    const LevelData& getLevel(int level) const;
};
