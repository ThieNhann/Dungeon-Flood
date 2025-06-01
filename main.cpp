#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"

using namespace std;

int main () { 

    const int SCREEN_WIDTH = 1440;
    const int SCREEN_HEIGHT = 900;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dungeon Flood");
    SetTargetFPS(60);

    PlayerTexture::LoadTextures();
    Fireball::LoadFireballTexture();
    GoblinTexture::LoadGoblinTextures();
    for (int i = 0; i < 10; ++i) {
        Enemy* g = new Goblin({500.0f + i*60, (float)(300 + i * 200)});
        EnemyManager::AddEnemy(g);
    }

    while (WindowShouldClose() == false){
        Player::Instance().Update();
        FireballManager::RemoveOutOfBoundFireballs();
        EnemyManager::Update();
        auto& fireballs = FireballManager::GetFireballs();
        auto& enemies = EnemyManager::GetEnemies();
        for (auto it = fireballs.begin(); it != fireballs.end();) {
            bool hit = false;
            for (auto& e : enemies) {
                if (CheckCollisionRecs(it->GetHitbox(), e->GetHitbox())) {
                    e->TakeDamage(it->GetDamage());
                    it = fireballs.erase(it);
                    hit = true;
                    break;
                }
            }
            if (!hit) ++it;
        }
        BeginDrawing();
            ClearBackground(BLACK);
            Player::Instance().DrawPlayer();
            FireballManager::Draw();
            EnemyManager::Draw();
        EndDrawing();
    }
    EnemyManager::Destruct();
    PlayerTexture::UnloadTextures();
    Fireball::UnloadFireballTexture();
    CloseWindow();
} 