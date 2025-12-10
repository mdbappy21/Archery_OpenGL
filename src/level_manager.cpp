#include "Level_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

int maxLevel=20;

void LevelManager::loadAll() {
    levels.clear();
    for(int i=1;i<=maxLevel;i++){
        std::string filename = "level_data/level-" + std::to_string(i) + ".txt";
        std::ifstream file(filename);
        if(!file.is_open()){
            std::cerr << "Cannot open " << filename << "\n";
            continue;
        }

        LevelData ld{};
        ld.levelNumber = i;
        ld.targetMoving = false;
        ld.barrierExists = false;

        std::string line;
        while(std::getline(file,line)){
            if(line.empty()) continue;
            std::replace(line.begin(), line.end(), '=', ' '); // allow '=' or space
            std::istringstream ss(line);
            std::string key; ss >> key;
            if(key=="targetX") ss >> ld.targetX;
            else if(key=="targetY") ss >> ld.targetY;
            else if(key=="targetRadius") ss >> ld.targetRadius;
            else if(key=="targetMoving") { int b; ss>>b; ld.targetMoving = b!=0; }
            else if(key=="targetMoveSpeed") ss >> ld.targetMoveSpeed;
            else if(key=="barrierExists") { int b; ss>>b; ld.barrierExists = b!=0; }
            else if(key=="barrierX") ss>>ld.barrierX;
            else if(key=="barrierY") ss>>ld.barrierY;
            else if(key=="barrierW") ss>>ld.barrierW;
            else if(key=="barrierH") ss>>ld.barrierH;
            else if(key=="barrierMoving") { int b; ss>>b; ld.barrierMoving = b!=0; }
            else if(key=="barrierMoveSpeed") ss>>ld.barrierMoveSpeed;
            else if(key=="gravity") ss>>ld.gravity;
        }
        file.close();
        levels.push_back(ld);
    }
}

const LevelData& LevelManager::getLevel(int level) const {
    for(const auto& ld : levels)
        if(ld.levelNumber == level) return ld;
    static LevelData dummy{};
    return dummy;
}
