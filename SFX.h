#ifndef SFX_H
#define SFX_H

#include <iostream>
#include <raylib.h>

class SFX {
public:
    static Sound fireball;
    static Sound goblinHurt;
    static Music bgMusic;
    static Sound boost;
    static Sound hurt;
public:
    static void LoadSFX();
    static void UnloadSFX();
};

#endif