#pragma once
#include <vector>
#include <string>

struct LevelData {
    int levelNumber;
    float targetX, targetY, targetRadius;
    bool targetMoving;
    float targetMoveSpeed;

    bool barrierExists;
    float barrierX, barrierY, barrierW, barrierH;
    bool barrierMoving;
    float barrierMoveSpeed;
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
