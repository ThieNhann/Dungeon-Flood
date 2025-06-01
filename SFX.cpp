#include "SFX.h"

Sound SFX::fireball;
Sound SFX::goblinHurt;
Music SFX::bgMusic;

void SFX::LoadSFX() {
    fireball = LoadSound("resources/sfx/fireballShoot.wav");
    goblinHurt = LoadSound("resources/sfx/goblinHurt.wav");
    bgMusic = LoadMusicStream("resources/sfx/time_for_adventure.mp3");
}

void SFX::UnloadSFX() {
    UnloadSound(fireball);
    UnloadSound(goblinHurt);
    UnloadMusicStream(bgMusic);
}