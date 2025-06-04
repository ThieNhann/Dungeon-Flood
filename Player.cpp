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

void Player::SetFireCooldown(float cd) {
    fireCooldown = cd;
}

float Player::GetFireCooldown() {
    return fireCooldown;
}

Player::Player() {
    health = PLAYER_HEALTH;
    direction = DOWN;
    hitbox.width = PLAYER_WIDTH;
    hitbox.height = PLAYER_HEIGHT;
    hitbox.x = PLAYER_START_X;
    hitbox.y = PLAYER_START_Y;
    speed = PLAYER_SPEED;
    texture.LoadTextures();
    fireCooldown = PLAYER_FIRE_COOLDOWN;
    multishotMode = false;
    piercingMode = false;
    damageInvincible = false;
    heartPlusInvincible = false;
}

Player& Player::Instance() {
    static Player instance;
    return instance;
}

Rectangle Player::GetHitbox() {
    return Player::Instance().hitbox;
}
void Player::DrawPlayer() {
    DrawTextureV(texture.GetTexture(direction), {hitbox.x, hitbox.y}, WHITE);
    if (GetInvincibleMode()) 
    {
        DrawTexture(IconTexture::heartProtection, hitbox.x + HEART_PROTECTION_OFFSET_X, hitbox.y + HEART_PROTECTION_OFFSET_Y, WHITE);
    }
}

void Player::SetPosition(Vector2 pos) {
    hitbox.x = pos.x;
    hitbox.y = pos.y;
}

int Player::GetHealth() {
    return health;
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

    static float lastHealthLossTime = -PLAYER_INVINCIBLE_TIME;
    float currentTime = GetTime();

    for (auto& en : EnemyManager::GetEnemies()) {
        if (!en->isDead() && CheckCollisionRecs(newHitbox, en->GetHitbox())) {
            // Only take damage if not currently damage-invincible
            if (!damageInvincible && (currentTime - lastHealthLossTime) >= PLAYER_INVINCIBLE_TIME) {
                if (GetHealth() > 0) {
                    SetHealth(GetHealth() - 1);
                }
                
                lastHealthLossTime = currentTime;
                SetDamageInvincible(true);
            }
            collision = true;
            break;
        }
    }
    // Turn off damage invincibility after duration
    if (damageInvincible && (currentTime - lastHealthLossTime) >= PLAYER_INVINCIBLE_TIME) {
        SetDamageInvincible(false);
    }

    for (auto& w : WallManager::GetWalls()) {
        if (CheckCollisionRecs(newHitbox, w->GetHitbox())) {
            collision = true;
            break;
        }
    }
    
    if (newHitbox.x >= SCREEN_WIDTH || newHitbox.x <= 0 || newHitbox.y <= 0 || newHitbox.y >= SCREEN_HEIGHT) collision = true;

    if (!collision) {
        hitbox.x = newHitbox.x;
        hitbox.y = newHitbox.y;
    }

    static float lastFireTime = 0.0f;
    float now = GetTime();

    Direction fireDirection;
    bool fire = false;
    if (IsKeyPressed(KEY_RIGHT)) {
        fireDirection = RIGHT;
        if (!IsWASDPressed()) direction = RIGHT;
        fire = true;
    } else if (IsKeyPressed(KEY_LEFT)) {
        fireDirection = LEFT;
        if (!IsWASDPressed()) direction = LEFT;
        fire = true;
    } else if (IsKeyPressed(KEY_UP)) {
        fireDirection = UP;
        if (!IsWASDPressed()) direction = UP;
        fire = true;
    } else if (IsKeyPressed(KEY_DOWN)) {
        fireDirection = DOWN;
        if (!IsWASDPressed()) direction = DOWN;
        fire = true;
    }
    if (fire && (now - lastFireTime) >= fireCooldown) {
        Fireball fireball({hitbox.x + MULTISHOT_OFFSET_X1, hitbox.y + MULTISHOT_OFFSET_Y3}, fireDirection);
        FireballManager::AddFireball(fireball);
        if (multishotMode) {
            if (fireDirection == RIGHT || fireDirection == LEFT) {
                Fireball additionalFireball1({hitbox.x + MULTISHOT_OFFSET_X1, hitbox.y + MULTISHOT_OFFSET_Y1}, fireDirection);
                FireballManager::AddFireball(additionalFireball1);
                Fireball additionalFireball2({hitbox.x + MULTISHOT_OFFSET_X1, hitbox.y + MULTISHOT_OFFSET_Y2}, fireDirection);
                FireballManager::AddFireball(additionalFireball2);
            } else {
                Fireball additionalFireball1({hitbox.x + MULTISHOT_OFFSET_X2, hitbox.y + MULTISHOT_OFFSET_Y3}, fireDirection);
                FireballManager::AddFireball(additionalFireball1);
                Fireball additionalFireball2({hitbox.x + MULTISHOT_OFFSET_X3, hitbox.y + MULTISHOT_OFFSET_Y3}, fireDirection);
                FireballManager::AddFireball(additionalFireball2);
            }
        }
        PlaySound(SFX::fireball);
        lastFireTime = now;
    }
}

Direction Player::GetDirection() {
    return direction;
}

void Player::SetDirection(Direction drt) {
    direction = drt;
}

void Player::SetMultishotMode(bool m) {
    multishotMode = m;
}

void Player::SetPiercingMode(bool m) {
    piercingMode = m;
}

bool Player::GetPiercingMode() {
    return piercingMode;
}

bool Player::GetInvincibleMode() {
    return damageInvincible || heartPlusInvincible;
}

void Player::SetDamageInvincible(bool m) {
    damageInvincible = m;
}

bool Player::GetDamageInvincible() {
    return damageInvincible;
}

void Player::SetHeartPlusInvincible(bool m) {
    heartPlusInvincible = m;
}

bool Player::GetHeartPlusInvincible() {
    return heartPlusInvincible;
}

void Player::SetHealth(int h) {
    health = h;
    if (h < GetHealth()) PlaySound(SFX::hurt);
}