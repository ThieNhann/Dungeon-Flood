#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Wall.h"

using namespace std;

int main () { 

    const int SCREEN_WIDTH = 1440;
    const int SCREEN_HEIGHT = 900;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dungeon Flood");
    SetTargetFPS(60);

    PlayerTexture::LoadTextures();
    Fireball::LoadFireballTexture();
    GoblinTexture::LoadGoblinTextures();
    VerticalWall::LoadWallTexture();
    HorizontalWall::LoadWallTexture();
    WallManager::InitCornerWalls();

    while (WindowShouldClose() == false){
        Player::Instance().Update();
        FireballManager::RemoveOutOfBoundFireballs();
        EnemyManager::Update();
        auto& fireballs = FireballManager::GetFireballs();
        for (auto it = fireballs.begin(); it != fireballs.end();) {
            bool hit = false;
            for (auto& e : EnemyManager::GetEnemies()) {
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
            WallManager::Draw();
        EndDrawing();
    }
    VerticalWall::UnloadWallTexture();
    HorizontalWall::UnloadWallTexture();
    EnemyManager::Destruct();
    PlayerTexture::UnloadTextures();
    Fireball::UnloadFireballTexture();
    WallManager::Destruct();
    CloseWindow();
}