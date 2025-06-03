#include "Items.h"

// --- Static/Global Variables ---
vector<Item*> ItemManager::items;
vector<Boost*> BoostManager::boosts;
Texture ItemTexture::fireSpeedBoost;
Texture ItemTexture::multishot;

// --- ItemTexture Implementation ---
void ItemTexture::LoadItemTexture() {
    fireSpeedBoost = LoadTexture("resources/images/fireSpeedBoost.png");
    multishot = LoadTexture("resources/images/multishot.png");
}

void ItemTexture::UnloadItemTexture() {
    UnloadTexture(fireSpeedBoost);
    UnloadTexture(multishot);
}

Texture ItemTexture::GetTexture(ItemType t) {
    switch (t) {
        case FIRESPEEDBOOST: return fireSpeedBoost;
        case MULTISHOT: return multishot;
        default: return fireSpeedBoost;
    }
}

// --- Item Implementation ---
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

bool Item::ShouldDespawn() const {
    return (GetTime() - spawnTime) >= 7.5f;
}

// --- Multishot Implementation ---
Multishot::Multishot(Vector2 pos) {
    texture = ItemTexture::GetTexture(MULTISHOT);
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.height = 32;
    hitbox.width = 32;
    effect = new MultishotEffect();
    spawnTime = GetTime();
}

// --- FireSpeedBoost Implementation ---
FireSpeedBoost::FireSpeedBoost(Vector2 pos) {
    texture = ItemTexture::GetTexture(FIRESPEEDBOOST);
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.height = 25;
    hitbox.width = 25;
    effect = new FireSpeedBoostEffect();
    spawnTime = GetTime();
}

// --- ItemManager Implementation ---
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
            PlaySound(SFX::boost);
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
    items.clear();
}

// --- Item Spawning Function ---
void ItemSpawn() {
    static std::vector<ItemType> types = { FIRESPEEDBOOST, MULTISHOT };
    static float lastSpawnTime = 0.0f;
    float now = GetTime();

    if (now - lastSpawnTime >= (float)GetRandomValue(10, 20)) {
        int typeIdx = GetRandomValue(0, types.size() - 1);
        ItemType type = types[typeIdx];
        float x = GetRandomValue(50, SCREEN_WIDTH - 75);
        float y = GetRandomValue(50, SCREEN_HEIGHT - 75);

        Item* item = nullptr;

        switch (type) {
            case FIRESPEEDBOOST:
                item = new FireSpeedBoost({x, y});
                break;
            case MULTISHOT:
                item = new Multishot({x, y});
                break;
        }
        
        if (item) ItemManager::AddItem(item);
        lastSpawnTime = now;
    }
}