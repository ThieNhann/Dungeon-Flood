#include "Enemy.h"

Texture GoblinTexture::goblinDown;
Texture GoblinTexture::goblinUp;
Texture GoblinTexture::goblinLeft;
Texture GoblinTexture::goblinRight;

vector<Enemy*> EnemyManager::enemies;

void GoblinTexture::LoadGoblinTextures() {
    goblinUp = LoadTexture("resources/images/goblinUp.png");
    goblinDown = LoadTexture("resources/images/goblinDown.png");
    goblinRight = LoadTexture("resources/images/goblinRight.png");
    goblinLeft = LoadTexture("resources/images/goblinLeft.png");
}

void GoblinTexture::UnloadGoblinTextures() {
    UnloadTexture(goblinUp);
    UnloadTexture(goblinDown);
    UnloadTexture(goblinRight);
    UnloadTexture(goblinLeft);

}
Texture GoblinTexture::GetCurrentTexture(Direction d) {
    switch (d) {
        case UP: return goblinUp;
        case DOWN: return goblinDown;
        case RIGHT: return goblinRight;
        case LEFT: return goblinLeft;
        default: return goblinDown; 
        break;
    }
}

void Goblin::Draw() {
    if (health > 0) {
        DrawTexture(texture.GetCurrentTexture(facing), hitbox.x, hitbox.y, WHITE);
    }
}

void Goblin::Update() {
    Vector2 playerPos = Player::Instance().GetPlayerPosition();
    Vector2 goblinPos = {hitbox.x, hitbox.y};
    Vector2 direction = {playerPos.x - goblinPos.x, playerPos.y - goblinPos.y};
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance != 0) {
        direction.x /= distance;
        direction.y /= distance;
    }

    if (fabs(direction.x) > fabs(direction.y)) {
        facing = (direction.x > 0) ? RIGHT : LEFT;
    } else {
        facing = (direction.y > 0) ? DOWN : UP;
    }

    float t = GetFrameTime();
    Vector2 newPos = {hitbox.x + direction.x * speed * t, hitbox.y + direction.y * speed * t};
    Rectangle newHitbox = hitbox;
    newHitbox.x = newPos.x;
    newHitbox.y = newPos.y;

    bool collision = false;
    for (auto& other : EnemyManager::GetEnemies()) {
        if (other != this && CheckCollisionRecs(newHitbox, other->GetHitbox())) {
            collision = true;
            break;
        }
    }

    for (auto& w : WallManager::GetWalls()) {
        if (CheckCollisionRecs(newHitbox, w->GetHitbox())) {
            collision = true;
            break;
        }
    }

    if (CheckCollisionRecs(newHitbox, Player::Instance().GetHitbox())) {
        collision = true;
    }

    if (!collision) {
        hitbox.x = newPos.x;
        hitbox.y = newPos.y;
    } else {
        Rectangle tryX = hitbox;
        tryX.x = hitbox.x + direction.x * speed * t;
        bool colX = false;
        for (auto& other : EnemyManager::GetEnemies()) {
            if (other != this && CheckCollisionRecs(tryX, other->GetHitbox())) {
                colX = true;
                break;
            }
        }
        if (!colX && !CheckCollisionRecs(tryX, Player::Instance().GetHitbox())) {
            hitbox.x = tryX.x;
            return;
        }

        Rectangle tryY = hitbox;
        tryY.y = hitbox.y + direction.y * speed * t;
        bool colY = false;
        for (auto& other : EnemyManager::GetEnemies()) {
            if (other != this && CheckCollisionRecs(tryY, other->GetHitbox())) {
                colY = true;
                break;
            }
        }
        if (!colY && !CheckCollisionRecs(tryY, Player::Instance().GetHitbox())) {
            hitbox.y = tryY.y;
            return;
        }
    }
}

Rectangle Goblin::GetHitbox() {
    return hitbox;
}

void Goblin::TakeDamage(int dmg) {
    if (dmg >= health) {
        health = 0;
    }
    else {
        health -= dmg;
    }
}

void Goblin::SetPosition(Vector2 pos) {
    hitbox.x = pos.x;
    hitbox.y = pos.y;
}


vector<Enemy*>& EnemyManager::GetEnemies() {
    return enemies;
}

void EnemyManager::AddEnemy(Enemy* en) {
    enemies.push_back(en);
}

void EnemyManager::Draw() {
    for (auto& e : enemies) {
        e->Draw();
    }
}

void EnemyManager::Update() {
    static float lastWaveSpawnTime = 0.0f;
    static int waveCounter = 1;
    float now = GetTime();
    if ((now - lastWaveSpawnTime) >= 5.0f) {
        Vector2 spawnPositions[4] = {
            {720, -50},   // Top gate
            {-50, 425},   // Left gate
            {1490, 425},  // Right gate
            {720, 950}    // Bottom gate
        };
        for (auto pos : spawnPositions) {
            for (int i = 0; i < waveCounter; i++) {
                float offsetX = (i % 3) * 45.0f;
                float offsetY = (i / 3) * 45.0f;
                Vector2 newSpawnPos = { pos.x + offsetX, pos.y + offsetY };
                EnemyManager::AddEnemy(new Goblin(newSpawnPos));
            }
        }
        if (waveCounter <= 8) waveCounter++;
        lastWaveSpawnTime = now;
    }

    for (auto it = enemies.begin(); it != enemies.end();) {
        if (!(*it)->isDead()) {
            (*it)->Update();
            ++it;
        } else {
            delete *it;
            it = enemies.erase(it);
        }
    }
}

void EnemyManager::Destruct() {
    for (auto& e : enemies) {
        delete e;
    }
}