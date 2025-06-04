#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <raylib.h>
#include <vector>
#include <algorithm>
#include "Wall.h"
#include "Config.h"
#include <set>
#include "Enemy.h"

class Enemy;

class Fireball {
private:
    static Texture texture;
    Rectangle hitbox;
    Direction direction;
    float speed;
    int damage;
public:
    std::set<Enemy*> enemiesHit;
public:
    Fireball(Vector2 pos, Direction d); 
    bool IsOutOfScreen() const;
    static void LoadFireballTexture();
    static void UnloadFireballTexture();
    void Draw();
    void Update();
    Rectangle GetHitbox() const;
    int GetDamage();
};

class FireballManager {
private:
    static std::vector<Fireball> fireballs;
public:
    static std::vector<Fireball>& GetFireballs();
    static void AddFireball(Fireball& f);
    static void Draw();
    static void RemoveOutOfBoundFireballs();
    static void Update();
    static void Destruct() {
        fireballs.clear();
    }
};


#endif