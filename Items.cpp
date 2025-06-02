#include "Items.h"

vector<Item*> ItemManager::items;
Texture ItemTexture::fireSpeedBoost;
vector<Boost*> BoostManager::boosts;

void ItemTexture::LoadItemTexture() {
    fireSpeedBoost = LoadTexture("resources/images/fireSpeedBoost.png");
}

void ItemTexture::UnloadItemTexture() {
    UnloadTexture(fireSpeedBoost);
}

Texture ItemTexture::GetTexture(ItemType t) {
    switch (t) {
        case FIRESPEEDBOOST: return fireSpeedBoost;
        default: return fireSpeedBoost;
    }
}
 
Rectangle Item::GetHitbox() {
    return hitbox;
}

void Item::Draw() {
    DrawTexture(texture, hitbox.x, hitbox.y, WHITE);
}

Boost* Item::GetBoost() {
    return effect;
}

void Item::Affect(Player& p) {
    BoostManager::AddBoost(GetBoost(), p);
}

FireSpeedBoost::FireSpeedBoost(Vector2 pos) {
    texture = ItemTexture::GetTexture(FIRESPEEDBOOST);
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.height = 25;
    hitbox.width = 25;
    effect = new FireSpeedBoostEffect();
}

vector<Item*>& ItemManager::GetItems() {
    return items;
}



void ItemManager::AddItem(Item* i) {
    items.push_back(i);
}

void ItemManager::Draw() {
    for (auto& i : items) {
        i->Draw();
    }
}

void ItemManager::Update() {
    Player& p = Player::Instance();
    for (auto it = items.begin(); it != items.end(); ) {
        if (CheckCollisionRecs(p.GetHitbox(), (*it)->GetHitbox())) {
            (*it)->Affect(p);
            delete *it;
            it = items.erase(it);
        } else {
            ++it;
        }
    }
}

void ItemManager::Destruct() {
    for (auto& i : items) {
        delete i;
    }
}