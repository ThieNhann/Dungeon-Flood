#include "Projectile.h"
#include "Player.h"

Texture Fireball::texture;
vector<Fireball> FireballManager::fireballs;

Fireball::Fireball(Vector2 pos, Direction d)  : direction(d) {
    speed = FIREBALL_SPEED;
    if (d == LEFT || d == RIGHT) {
        hitbox.height = FIREBALL_HEIGHT_H;
        hitbox.width = FIREBALL_WIDTH_H;
    }
    else { 
        hitbox.height = FIREBALL_HEIGHT_V;
        hitbox.width = FIREBALL_WIDTH_V;
    }
    damage = FIREBALL_DAMAGE;
    hitbox.x = pos.x;
    hitbox.y = pos.y;
}

void Fireball::LoadFireballTexture() {
    texture = LoadTexture("resources/images/fireball.png");
}

void Fireball::UnloadFireballTexture() {
    UnloadTexture(texture);
}

void Fireball::Draw() {
    float rotation = 0; 
    switch (direction) {
        case UP: rotation = -90.0f; break;
        case DOWN: rotation = 90.0f; break;
        case RIGHT: rotation = 0.0f; break;
        case LEFT: rotation = 180.0f; break;
        default: break;
    }
    Vector2 texturePos = {hitbox.x, hitbox.y};
    switch (direction) {
        case RIGHT:
            break;
        case UP:
            texturePos.y += hitbox.height;
            break;
        case DOWN:
            texturePos.x += hitbox.width;
            break;
        case LEFT:
            texturePos.y += hitbox.height;
            texturePos.x += hitbox.width;
            break;
        default:
            break;
    }
    DrawTextureEx(texture, texturePos, rotation, 1.0f, WHITE);
}

void Fireball::Update() {
    float t = GetFrameTime();
    switch (direction) {
        case UP: hitbox.y -= speed*t; break;
        case DOWN: hitbox.y += speed*t; break;
        case LEFT: hitbox.x -= speed*t; break;
        case RIGHT: hitbox.x += speed*t; break;
        default: break;
    }
}

bool Fireball::IsOutOfScreen() const {
    return hitbox.x < 0 || hitbox.x > SCREEN_WIDTH || hitbox.y < 0 || hitbox.y > SCREEN_HEIGHT;
}

Rectangle Fireball::GetHitbox() const { return hitbox; }
int Fireball::GetDamage() { return damage; }

void FireballManager::Draw() {
    for (auto& f : fireballs) {
        f.Draw();
    }
}

void FireballManager::RemoveOutOfBoundFireballs() {
    for (auto& f : fireballs) {
        f.Update();
    }
    fireballs.erase(remove_if(fireballs.begin(), fireballs.end(), [](const Fireball& f) {
        for (auto& w : WallManager::GetWalls()) {
            if (CheckCollisionRecs(w->GetHitbox(), f.GetHitbox())) {
                return true;
            }
        }
        return f.IsOutOfScreen();
    }),
    fireballs.end());
}

void FireballManager::AddFireball(Fireball& f) {
    fireballs.push_back(f);
} 

vector<Fireball>& FireballManager::GetFireballs() {
    return fireballs;
}

void FireballManager::Update() {
    auto& fireballs = GetFireballs();
    for (auto it = fireballs.begin(); it != fireballs.end();) {
        bool hit = false;
        for (auto& e : EnemyManager::GetEnemies()) {
            if (CheckCollisionRecs(it->GetHitbox(), e->GetHitbox())) {
                if (Player::Instance().GetPiercingMode()) {
                    if (it->enemiesHit.count(e) == 0 && it->enemiesHit.size() < 3) {
                        e->TakeDamage(it->GetDamage());
                        PlaySound(SFX::goblinHurt);
                        it->enemiesHit.insert(e);
                        if (it->enemiesHit.size() >= 3) {
                            it = fireballs.erase(it);
                            hit = true;
                            break;
                        }
                    }
                } else {
                    e->TakeDamage(it->GetDamage());
                    PlaySound(SFX::goblinHurt);
                    it = fireballs.erase(it);
                    hit = true;
                    break;
                }
            }
        }
        if (!hit) ++it;
    }
}