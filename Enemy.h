#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include <raylib.h>
#include "Config.h"
#include <cmath>

class GoblinTexture {
private:
    static Texture goblinUp;
    static Texture goblinDown;
    static Texture goblinRight;
    static Texture goblinLeft;
public:
    static void LoadGoblinTextures();
    static void UnloadGoblinTextures();
    Texture GetCurrentTexture(Direction d);
};

class Enemy {
protected:
    int health;
    Rectangle hitbox;
    GoblinTexture texture;
    float speed;
    Direction facing;
public:
    bool isDead() { return health == 0; }
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual ~Enemy() {}
};

class Goblin : public Enemy {
public:
    Goblin() {
        health = 1;
        hitbox.height = 64;
        hitbox.height = 64;
        hitbox.y = 450;
        hitbox.x = 0;
        speed = 150;
        facing = DOWN;
    }
    void Draw();
    void Update();
};

#endif