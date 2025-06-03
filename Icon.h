#ifndef ICON_H
#define ICON_H

#include "raylib.h"

class IconTexture {
public:
    static Texture heart;
    static Texture heartProtection;
public:
    static void LoadIconTexture();
    static void UnloadIconTexture();
};

#endif