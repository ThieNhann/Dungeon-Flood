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

    if (CheckCollisionRecs(newHitbox, Player::Instance().GetHitbox())) {
        collision = true;
    }

    if (!collision) {
        hitbox.x = newPos.x;
        hitbox.y = newPos.y;
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
    for (auto& e : enemies) {
        e->Update();
    }
    enemies.erase(remove_if(enemies.begin(), enemies.end(), [](const Enemy* e) {
        return e->isDead();
    }),
    enemies.end());
}

void EnemyManager::Destruct() {
    for (auto& e : enemies) {
        delete e;
    }
}