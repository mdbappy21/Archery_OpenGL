#pragma once
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

namespace SoundManager {
    void playHomeMusic();
    void stopHomeMusic();

    void playOverlayMusic();
    void stopOverlayMusic();

    void playHitSound();
    void playMissSound();
}
