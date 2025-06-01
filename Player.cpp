#include "Player.h"

Texture PlayerTexture::up;
Texture PlayerTexture::down;
Texture PlayerTexture::left;
Texture PlayerTexture::right;

void PlayerTexture::LoadTextures()  {
    up = LoadTexture("resources/images/playerUp.png");
    down = LoadTexture("resources/images/playerDown.png");
    left = LoadTexture("resources/images/playerLeft.png");
    right = LoadTexture("resources/images/playerRight.png");
}

void PlayerTexture::UnloadTextures() {
    UnloadTexture(up);
    UnloadTexture(down);
    UnloadTexture(left);
    UnloadTexture(right);
}

Vector2 Player::GetPlayerPosition() {
    return {hitbox.x, hitbox.y};
}

Player::Player() {
    direction = DOWN;
    hitbox.width = 40;
    hitbox.height = 40;
    hitbox.x = 720;
    hitbox.y = 450;
    speed = PLAYER_SPEED;
    texture.LoadTextures();
}

Player& Player::Instance() {
    static Player instance;
    return instance;
}

Rectangle Player::GetHitbox() {
    return Player::Instance().hitbox;
}
void Player::DrawPlayer() {
    DrawTextureV(texture.GetTexture(direction), GetPlayerPosition(), WHITE);
}

void Player::SetPosition(Vector2 pos) {
    hitbox.x = pos.x;
    hitbox.y = pos.y;
}

void Player::Update() {
    float t = GetFrameTime();
    Vector2 newPos = {hitbox.x, hitbox.y};

    if (IsKeyDown(KEY_W)) {
        SetDirection(UP);
        newPos.y -= t * speed;  
    }
    if (IsKeyDown(KEY_S)) {
        SetDirection(DOWN);
        newPos.y += t * speed;
    }
    if (IsKeyDown(KEY_D)) {
        SetDirection(RIGHT); 
        newPos.x += t * speed;
    }
    if (IsKeyDown(KEY_A)) {
        SetDirection(LEFT);
        newPos.x -= t * speed;
    }

    Rectangle newHitbox = hitbox;
    newHitbox.x = newPos.x;
    newHitbox.y = newPos.y;

    bool collision = false;

    for (auto& en : EnemyManager::GetEnemies()) {
        if (!en ->isDead() && CheckCollisionRecs(newHitbox, en->GetHitbox())) {
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
    
    if (!collision) {
        hitbox.x = newHitbox.x;
        hitbox.y = newHitbox.y;
    }

    static float lastFireTime = 0.0f;
    const float fireCooldown = 0.25f; // giây
    float now = GetTime();

    Direction fireDirection;
    bool fire = false;
    if (IsKeyPressed(KEY_RIGHT)) {
        fireDirection = RIGHT;
        direction = RIGHT;
        fire = true;
    } else if (IsKeyPressed(KEY_LEFT)) {
        fireDirection = LEFT;
        direction = LEFT;
        fire = true;
    } else if (IsKeyPressed(KEY_UP)) {
        fireDirection = UP;
        direction = UP;
        fire = true;
    } else if (IsKeyPressed(KEY_DOWN)) {
        fireDirection = DOWN;
        direction = DOWN;
        fire = true;
    }
    if (fire && (now - lastFireTime) >= fireCooldown) {
        Fireball fireball({hitbox.x + 15, hitbox.y + 10}, fireDirection);
        FireballManager::AddFireball(fireball);
        lastFireTime = now;
    }
}

Direction Player::GetDirection() {
    return direction;
}

void Player::SetDirection(Direction drt) {
    direction = drt;
}