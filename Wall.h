#ifndef WALL_H
#define WALL_H

#include <raylib.h>
#include <vector>
#include "Config.h"

class RectWall {
protected:
    Rectangle hitbox;
public:
    virtual void Draw() = 0;
    virtual ~RectWall() {}
    Rectangle GetHitbox() { return hitbox; }
};

class VerticalWall : public RectWall {
private:
    static Texture texture;
public:
    void Draw();
    VerticalWall(Vector2 pos);
    static void LoadWallTexture();
    static void UnloadWallTexture();
};

class HorizontalWall : public RectWall {
private:
    static Texture texture;
public:
    void Draw();
    HorizontalWall(Vector2 pos);
    static void LoadWallTexture();
    static void UnloadWallTexture();
};

class WallManager {
public:
    static std::vector<RectWall*> walls;
    static void InitCornerWalls();
    static void Draw();
    static std::vector<RectWall*>& GetWalls();
    static void Destruct();
};


#endif