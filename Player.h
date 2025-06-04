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
    bool piercingMode;
    bool damageInvincible;      // new: for damage invincibility
    bool heartPlusInvincible;   // new: for HeartPlus item invincibility
public:
    void SetHealth(int h);
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

    // invincibleMode is now a derived property
    bool GetInvincibleMode();

    // New: invincibility source management
    void SetDamageInvincible(bool m);
    bool GetDamageInvincible();
    void SetHeartPlusInvincible(bool m);
    bool GetHeartPlusInvincible();
};

#endif