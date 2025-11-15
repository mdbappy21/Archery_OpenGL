#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>

inline float clampf(float v, float a, float b) { return v < a ? a : (v > b ? b : v); }
inline float deg2rad(float d) { return d * 3.14159f / 180.0f; }

// seed RNG
static inline void seedRandom() { static bool seeded = false; if (!seeded) { std::srand((unsigned)std::time(nullptr)); seeded = true; } }
