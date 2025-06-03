#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <iostream>
#include "Projectile.h"
#include "Enemy.h"
#include "Wall.h"
#include "SFX.h"
#include "Utils.h"
#include "Icon.h"

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
    int health;
    bool multishotMode;
    bool invincibleMode;
    bool piercingMode;
public:
    int GetHealth();
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
    void SetMultishotMode(bool m);
    void SetPiercingMode(bool m);
    bool GetPiercingMode();
};

#endif