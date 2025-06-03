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
    Player p = Player::Instance();
    Vector2 playerPos = { p.GetHitbox().x, p.GetHitbox().y };
    Vector2 goblinPos = {hitbox.x, hitbox.y};

    Vector2 toPlayer = {playerPos.x - goblinPos.x, playerPos.y - goblinPos.y};
    float distToPlayer = sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
    
    if (distToPlayer != 0) {
        toPlayer.x /= distToPlayer;
        toPlayer.y /= distToPlayer;
    }

    Vector2 separation = {0, 0};
    const float SEPARATION_RADIUS = GOBLIN_SEPARATION_RADIUS;
    int neighborCount = 0;

    for (auto& other : EnemyManager::GetEnemies()) {
        if (other != this) {
            Vector2 otherPos = {other->GetHitbox().x, other->GetHitbox().y};
            Vector2 diff = {goblinPos.x - otherPos.x, goblinPos.y - otherPos.y};
            float dist = sqrt(diff.x * diff.x + diff.y * diff.y);
            
            if (dist < SEPARATION_RADIUS && dist > 0) {
                separation.x += diff.x / dist;
                separation.y += diff.y / dist;
                neighborCount++;
            }
        }
    }

    if (neighborCount > 0) {
        float sepMag = sqrt(separation.x * separation.x + separation.y * separation.y);
        if (sepMag > 0) {
            separation.x /= sepMag;
            separation.y /= sepMag;
        }
    }

    const float CHASE_WEIGHT = GOBLIN_CHASE_WEIGHT;
    const float SEPARATION_WEIGHT = GOBLIN_SEPARATION_WEIGHT;
    
    Vector2 direction = {
        toPlayer.x * CHASE_WEIGHT + separation.x * SEPARATION_WEIGHT,
        toPlayer.y * CHASE_WEIGHT + separation.y * SEPARATION_WEIGHT
    };

    float dirLength = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (dirLength > 0) {
        direction.x /= dirLength;
        direction.y /= dirLength;
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
        for (auto& w : WallManager::GetWalls()) {
            if (CheckCollisionRecs(tryX, w->GetHitbox())) {
                colX = true;
                break;
            }
        }
        if (!colX && !CheckCollisionRecs(tryX, Player::Instance().GetHitbox())) {
            hitbox.x = tryX.x;
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
        for (auto& w : WallManager::GetWalls()) {
            if (CheckCollisionRecs(tryY, w->GetHitbox())) {
                colY = true;
                break;
            }
        }
        if (!colY && !CheckCollisionRecs(tryY, Player::Instance().GetHitbox())) {
            hitbox.y = tryY.y;
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
    if ((now - lastWaveSpawnTime) >= ENEMY_SPAWN_INTERVAL) {
        Vector2 spawnPositions[4] = {
            {720, -60},
            {-60, 425},
            {1460, 425},
            {720, 910}
        };
        for (auto pos : spawnPositions) {
            for (int i = 0; i < waveCounter; i++) {
                float offsetX = (i % 3) * ENEMY_SPAWN_WIDTH;
                float offsetY = (i / 3) * ENEMY_SPAWN_HEIGHT;
                Vector2 newSpawnPos = { pos.x + offsetX, pos.y + offsetY };

                bool validPosition = true;
                for (auto& e : EnemyManager::GetEnemies()) {
                    if (CheckCollisionRecs(Rectangle{newSpawnPos.x, newSpawnPos.y, ENEMY_SPAWN_WIDTH, ENEMY_SPAWN_HEIGHT}, e->GetHitbox())) {
                        validPosition = false;
                        break;
                    }
                }
                for (auto& w : WallManager::GetWalls()) {
                    if (CheckCollisionRecs(Rectangle{newSpawnPos.x, newSpawnPos.y, ENEMY_SPAWN_WIDTH, ENEMY_SPAWN_HEIGHT}, w->GetHitbox())) {
                        validPosition = false;
                        break;
                    }
                }

                if (validPosition) {
                    EnemyManager::AddEnemy(new Goblin(newSpawnPos));
                }
            }
        }
        if (waveCounter <= ENEMY_SPAWN_WAVE_MAX) waveCounter++;
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