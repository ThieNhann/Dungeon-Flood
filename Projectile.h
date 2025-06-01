#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <raylib.h>
#include <vector>
#include <algorithm>
#include "Wall.h"
#include "Config.h"

using namespace std;

class Fireball {
private:
    static Texture texture;
    Rectangle hitbox;
    Direction direction;
    float speed;
    int damage;
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
    static vector<Fireball> fireballs;
public:
    static vector<Fireball>& GetFireballs();
    static void AddFireball(Fireball& f);
    static void Draw();
    static void RemoveOutOfBoundFireballs();
};


#endif