#include "level_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

int maxLevel = 20;

void LevelManager::loadAll() {
    levels.clear();
    for (int i = 1; i <= maxLevel; ++i) {
        std::string filename = "level_data/level-" + std::to_string(i) + ".txt";
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Cannot open " << filename << "\n";
            continue;
        }

        LevelData ld{};
        ld.levelNumber = i;

        // default values (safe)
        ld.targetX = 650; ld.targetY = 250; ld.targetRadius = 50;
        ld.targetMoving = 0; ld.targetMoveSpeed = 0.0f; ld.targetReflectionEnabled = 0;
        ld.barrierExists = 0; ld.barrierX = 0; ld.barrierY = 0; ld.barrierW = 0; ld.barrierH = 0;
        ld.barrierMoving = 0; ld.barrierMoveSpeed = 0.0f;
        ld.barrierRotateEnabled = 0; ld.barrierRotateSpeed = 0.0f;
        ld.barrierScalingEnabled = 0; ld.barrierScaleOnTrigger = 1.0f;
        ld.gravity = -600.0f;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            // Allow format: key value  OR key=value
            std::replace(line.begin(), line.end(), '=', ' ');
            std::istringstream ss(line);
            std::string key;
            ss >> key;
            if (key == "targetX") ss >> ld.targetX;
            else if (key == "targetY") ss >> ld.targetY;
            else if (key == "targetRadius") ss >> ld.targetRadius;
            else if (key == "targetMoving") { int b; ss >> b; ld.targetMoving = b; }
            else if (key == "targetMoveSpeed") ss >> ld.targetMoveSpeed;
            else if (key == "targetReflectionEnabled") { int b; ss >> b; ld.targetReflectionEnabled = b; }

            else if (key == "barrierExists") { int b; ss >> b; ld.barrierExists = b; }
            else if (key == "barrierX") ss >> ld.barrierX;
            else if (key == "barrierY") ss >> ld.barrierY;
            else if (key == "barrierW") ss >> ld.barrierW;
            else if (key == "barrierH") ss >> ld.barrierH;
            else if (key == "barrierMoving") { int b; ss >> b; ld.barrierMoving = b; }
            else if (key == "barrierMoveSpeed") ss >> ld.barrierMoveSpeed;

            else if (key == "barrierRotateEnabled") { int b; ss >> b; ld.barrierRotateEnabled = b; }
            else if (key == "barrierRotateSpeed") ss >> ld.barrierRotateSpeed;

            else if (key == "barrierScalingEnabled") { int b; ss >> b; ld.barrierScalingEnabled = b; }
            else if (key == "barrierScaleOnTrigger") ss >> ld.barrierScaleOnTrigger;

            else if (key == "gravity") ss >> ld.gravity;
        }
        file.close();
        levels.push_back(ld);
    }
}

const LevelData& LevelManager::getLevel(int level) const {
    for (const auto& ld : levels)
        if (ld.levelNumber == level) return ld;
    static LevelData dummy{};
    return dummy;
}
