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
    DrawRectangle(hitbox.x, hitbox.y, hitbox.width, hitbox.height, Color{255, 255, 0, 100});
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
    spawnTime = GetTime();
}

bool Item::ShouldDespawn() const {
    return (GetTime() - spawnTime) >= 5.0f;
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
        } else if ((*it)->ShouldDespawn()) {
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

void ItemSpawn() {
    static std::vector<ItemType> types = { FIRESPEEDBOOST };
    static float lastSpawnTime = 0.0f;
    float now = GetTime();

    if (now - lastSpawnTime >= 15.0f) {
        int typeIdx = GetRandomValue(0, types.size() - 1);
        ItemType type = types[typeIdx];
        float x = GetRandomValue(50, SCREEN_WIDTH - 75);
        float y = GetRandomValue(50, SCREEN_HEIGHT - 75);

        Item* item = nullptr;

        switch (type) {
            case FIRESPEEDBOOST:
                item = new FireSpeedBoost({x, y});
                break;
        }
        
        if (item) ItemManager::AddItem(item);
        lastSpawnTime = now;
    }
}