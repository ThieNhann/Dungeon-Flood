#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"
#include <raylib.h>
#include "Config.h"
#include <cmath>
#include "Wall.h"

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

class MushroomTexture {
private:
    static Texture mushroomUp;
    static Texture mushroomDown;
    static Texture mushroomRight;
    static Texture mushroomLeft;
public:
    static void LoadMushroomTextures();
    static void UnloadMushroomTextures();
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
    Rectangle GetHitbox();
    void TakeDamage(int dmg);
    virtual void Draw();
    virtual void Update();
    void SetPosition(Vector2 pos);
    virtual ~Enemy() {}
};

class EnemyManager {
private:
    static vector<Enemy*> enemies;
    static int goblinWaves;
    static int mushroomWaves;
    static const int MAX_GOBLIN_WAVES = 7;
    static const int MAX_MUSHROOM_WAVES = 5;
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
        health = GOBLIN_HEALTH;
        hitbox.x = pos.x;
        hitbox.y = pos.y;
        hitbox.width = GOBLIN_WIDTH;
        hitbox.height = GOBLIN_HEIGHT;
        speed = GOBLIN_SPEED;
        facing = DOWN;
    }
    void Draw();
    void Update();
};

class Mushroom : public Enemy {
private:
    MushroomTexture texture;
public:
    Mushroom(Vector2 pos) {
        health = MUSHROOM_HEALTH; // Mushroom health
        hitbox.x = pos.x;
        hitbox.y = pos.y;
        hitbox.width = MUSHROOM_WIDTH;
        hitbox.height = MUSHROOM_HEIGHT;
        speed = MUSHROOM_SPEED; // Mushroom speed
        facing = DOWN;
    }
    void Draw();
    void Update();
};

#endif