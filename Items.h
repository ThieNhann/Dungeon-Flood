#ifndef ITEMS_H
#define ITEMS_H

#include <raylib.h>
#include "Player.h"
#include <vector>
#include "Boost.h"

enum ItemType { FIRESPEEDBOOST };

class ItemTexture {
public:
    static Texture fireSpeedBoost;
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
public:
    virtual ~Item() {}
    Boost* GetBoost();
    void Affect(Player& p);
    Rectangle GetHitbox();
    void Draw();
};

class FireSpeedBoost : public Item {
public:
    FireSpeedBoost(Vector2 pos);
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