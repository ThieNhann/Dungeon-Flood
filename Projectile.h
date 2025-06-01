#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <raylib.h>
#include <vector>
#include <algorithm>
#include "Config.h" // Add this include

using namespace std;

class Fireball {
private:
    static Texture texture;
    Rectangle hitbox;
    Direction direction;
    float speed; 
public:
    Fireball(Vector2 pos, Direction d);
    bool IsOutOfScreen() const;
    static void LoadFireballTexture();
    static void UnloadFireballTexture();
    void Draw();
    void Update();
};

class FireballManager {
private:
    static vector<Fireball> fireballs;
public:
    static void AddFireball(Fireball& f);
    static void Draw();
    static void RemoveOutOfBoundFireballs();
};


#endif