#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <iostream>
#include "Projectile.h"
#include "Enemy.h"
#include "Wall.h"
#include "SFX.h"

class PlayerTexture {
private:
    static Texture up;
    static Texture down;
    static Texture left;
    static Texture right;
public:
    static void LoadTextures();
    static void UnloadTextures();
    Texture GetTexture(Direction d) {
        switch (d) {
            case LEFT: return left;
            case RIGHT: return right;
            case UP: return up;
            default: return down;
        }
    } 
};

class Player {
private:
    PlayerTexture texture;
    Rectangle hitbox;
    Direction direction;
    int speed;
    float fireCooldown;
public:
    static Player& Instance();
    static Rectangle GetHitbox();
    Player();
    void Update();
    Direction GetDirection();
    void SetDirection(Direction);
    void SetPosition(Vector2);
    void SetFireCooldown(float);
    float GetFireCooldown();
    void DrawPlayer();
};

#endif