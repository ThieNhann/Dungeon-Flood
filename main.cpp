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

    for (int i = 0; i < 5; ++i) {
        Enemy* g = new Goblin({700.0f, (float)(200 + i * 100)});
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
            WallManager::Draw();
            /*DrawRectangle(820, 0, 620, 50, GREEN);
            DrawRectangle(0, 0, 620, 50, GREEN);
            DrawRectangle(0, 0, 50, 350, GREEN);
            DrawRectangle(0, 500, 50, 350, GREEN);*/
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