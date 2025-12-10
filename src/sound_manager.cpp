#include "sound_manager.h"

namespace SoundManager {

void playHomeMusic() {
    PlaySound("sounds/home.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void stopHomeMusic() {
    PlaySound(NULL, NULL, 0);
}

void playOverlayMusic() {
    PlaySound("sounds/overlay.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void stopOverlayMusic() {
    PlaySound(NULL, NULL, 0);
}

void playHitSound() {
    sndPlaySound("sounds/hit.wav", SND_FILENAME | SND_ASYNC);
}

void playMissSound() {
    sndPlaySound("sounds/miss.wav", SND_FILENAME | SND_ASYNC);
}

} // namespace SoundManager
