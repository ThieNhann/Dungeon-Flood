#include "Items.h"

// --- Static/Global Variables ---
vector<Item*> ItemManager::items;
vector<Boost*> BoostManager::boosts;
Texture ItemTexture::fireSpeedBoost;
Texture ItemTexture::multishot;
Texture ItemTexture::piercing;
Texture ItemTexture::heartPlus;

// --- ItemTexture Implementation ---
void ItemTexture::LoadItemTexture() {
    fireSpeedBoost = LoadTexture("resources/images/fireSpeedBoost.png");
    multishot = LoadTexture("resources/images/multishot.png");
    piercing = LoadTexture("resources/images/piercing.png");
    heartPlus = LoadTexture("resources/images/heartPlus.png");
}

void ItemTexture::UnloadItemTexture() {
    UnloadTexture(fireSpeedBoost);
    UnloadTexture(multishot);
    UnloadTexture(piercing);
    UnloadTexture(heartPlus);
}

Texture ItemTexture::GetTexture(ItemType t) {
    switch (t) {
        case FIRESPEEDBOOST: return fireSpeedBoost;
        case MULTISHOT: return multishot;
        case PIERCING: return piercing;
        case HEARTPLUS: return heartPlus;
        default: return fireSpeedBoost;
    }
}

// --- Item Implementation ---
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

bool Item::ShouldDespawn() const {
    return (GetTime() - spawnTime) >= ITEM_DESPAWN_TIME;
}

// --- Multishot Implementation ---
Multishot::Multishot(Vector2 pos) {
    texture = ItemTexture::GetTexture(MULTISHOT);
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.height = ITEM_HEIGHT;
    hitbox.width = ITEM_WIDTH;
    effect = new MultishotEffect();
    spawnTime = GetTime();
}

// --- FireSpeedBoost Implementation ---
FireSpeedBoost::FireSpeedBoost(Vector2 pos) {
    texture = ItemTexture::GetTexture(FIRESPEEDBOOST);
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.height = ITEM_HEIGHT;
    hitbox.width = ITEM_WIDTH;
    effect = new FireSpeedBoostEffect();
    spawnTime = GetTime();
}

// --- Piercing Implementation ---
Piercing::Piercing(Vector2 pos) {
    texture = ItemTexture::GetTexture(PIERCING);
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.height = ITEM_HEIGHT;
    hitbox.width = ITEM_WIDTH;
    effect = new PiercingEffect();
    spawnTime = GetTime();
}

HeartPlus::HeartPlus(Vector2 pos) {
    texture = ItemTexture::GetTexture(HEARTPLUS);
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.height = ITEM_HEIGHT;
    hitbox.width = ITEM_WIDTH;
    effect = new HeartPlusEffect();
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
    static std::vector<ItemType> types = { FIRESPEEDBOOST, MULTISHOT, PIERCING, HEARTPLUS};
    static float lastSpawnTime = 0.0f;
    float now = GetTime();

    if (now - lastSpawnTime >= (float)GetRandomValue((int)ITEM_SPAWN_MIN_TIME, (int)ITEM_SPAWN_MAX_TIME)) {
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
            case PIERCING:
                item = new Piercing({x, y});
                break;
            case HEARTPLUS:
                item = new HeartPlus({x, y});
                break;
        }
        
        if (item) ItemManager::AddItem(item);
        lastSpawnTime = now;
    }
}