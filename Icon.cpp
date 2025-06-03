#include "Icon.h"

Texture IconTexture::heart;
Texture IconTexture::heartProtection;

void IconTexture::LoadIconTexture() {
    heart = LoadTexture("resources/images/heart.png");
    heartProtection = LoadTexture("resources/images/heartProtection.png");
}
void IconTexture::UnloadIconTexture() {
    UnloadTexture(heart);
    UnloadTexture(heartProtection);
}