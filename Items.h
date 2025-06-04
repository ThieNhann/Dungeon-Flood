#ifndef ITEMS_H
#define ITEMS_H

#include <raylib.h>
#include "Player.h"
#include <vector>
#include "Boost.h"
#include "SFX.h"

enum ItemType { FIRESPEEDBOOST, MULTISHOT, PIERCING, HEARTPLUS };

class ItemTexture {
public:
    static Texture fireSpeedBoost;
    static Texture multishot;
    static Texture piercing;
    static Texture heartPlus;
public:
    static void LoadItemTexture();
    static void UnloadItemTexture();
    static Texture GetTexture(ItemType t);
};

class Item {
protected:
    Rectangle hitbox;
    Texture texture;
    Boost* effect;
    float spawnTime;
public:
    virtual ~Item() {}
    Boost* GetBoost();
    void Affect(Player& p);
    Rectangle GetHitbox();
    void Draw();
    bool ShouldDespawn() const;
};

class Multishot : public Item {
public:
    Multishot(Vector2 pos);
};

class FireSpeedBoost : public Item {
public:
    FireSpeedBoost(Vector2 pos);
};

class Piercing : public Item {
public:
    Piercing(Vector2 pos);
};

class HeartPlus: public Item {
public:
    HeartPlus(Vector2 pos);
};

class ItemManager {
public:
    static std::vector<Item*> items;
public:
    static std::vector<Item*>& GetItems();
    static void AddItem(Item* i);
    static void Update();
    static void Draw();
    static void Destruct();
};

void ItemSpawn();

#endif