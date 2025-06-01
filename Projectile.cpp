#include "Projectile.h"

Texture Fireball::texture;
vector<Fireball> FireballManager::fireballs;

Fireball::Fireball(Vector2 pos, Direction d)  : direction(d) {
    speed = 300;
    hitbox.height = 7;
    hitbox.width = 13;
    hitbox.x = pos.x;
    hitbox.y = pos.y;
}

void Fireball::LoadFireballTexture() {
    texture = LoadTexture("resources/images/fireball.png");
}

void Fireball::UnloadFireballTexture() {
    UnloadTexture(texture);
}

void Fireball::Draw() {
    float rotation = 0; 
    switch (direction) {
        case UP: rotation = -90.0f; break;
        case DOWN: rotation = 90.0f; break;
        case RIGHT: rotation = 0.0f; break;
        case LEFT: rotation = 180.0f; break;
        default: break;
    }
    DrawTextureEx(texture, {hitbox.x, hitbox.y + 43}, rotation, 1.0f, WHITE);
}

void Fireball::Update() {
    float t = GetFrameTime();
    switch (direction) {
        case UP: hitbox.y -= speed*t; break;
        case DOWN: hitbox.y += speed*t; break;
        case LEFT: hitbox.x -= speed*t; break;
        case RIGHT: hitbox.x += speed*t; break;
        default: break;
    }
}

bool Fireball::IsOutOfScreen() const {
    return hitbox.x < 0 || hitbox.x > 1440 || hitbox.y < 0 || hitbox.y > 900;
}


void FireballManager::Draw() {
    for (auto& f : fireballs) {
        f.Draw();
    }
}

void FireballManager::RemoveOutOfBoundFireballs() {
    for (auto& f : fireballs) {
        f.Update();
    }
    fireballs.erase(remove_if(fireballs.begin(), fireballs.end(), [](const Fireball& f) {
        return f.IsOutOfScreen();
    }),
    fireballs.end());
}

void FireballManager::AddFireball(Fireball& f) {
    fireballs.push_back(f);
}