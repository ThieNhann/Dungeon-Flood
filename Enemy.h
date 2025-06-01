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
    bool isDead() const { return health == 0; }
    virtual Rectangle GetHitbox() = 0;
    virtual void TakeDamage(int dmg) = 0;
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual ~Enemy() {}
};

class EnemyManager {
private:
    static vector<Enemy*> enemies;
public:
    static vector<Enemy*>& GetEnemies();
    static void AddEnemy(Enemy* en);
    static void Draw();
    static void Update();
    static void Destruct();
};

class Goblin : public Enemy {
public:
    Goblin(Vector2 pos) {
        health = 1;
        hitbox.x = pos.x;
        hitbox.y = pos.y;
        hitbox.width = 35;
        hitbox.height = 35;
        speed = 100;
        facing = DOWN;
    }
    void Draw();
    void Update();
    Rectangle GetHitbox();
    void TakeDamage(int dmg);
    void SetPosition(Vector2);
};

#endif