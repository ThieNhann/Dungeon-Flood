#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Wall.h"
#include "SFX.h"
#include "Items.h"
using namespace std;

int main () { 

    const int SCREEN_WIDTH = 1440;
    const int SCREEN_HEIGHT = 900;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dungeon Flood");
    InitAudioDevice();
    SetTargetFPS(60);

    PlayerTexture::LoadTextures();
    Fireball::LoadFireballTexture();
    GoblinTexture::LoadGoblinTextures();
    VerticalWall::LoadWallTexture();
    HorizontalWall::LoadWallTexture();
    WallManager::InitCornerWalls();
    SFX::LoadSFX();
    ItemTexture::LoadItemTexture();

    Texture2D background = LoadTexture("resources/images/background.png");

    PlayMusicStream(SFX::bgMusic);
    while (WindowShouldClose() == false){

        UpdateMusicStream(SFX::bgMusic);
        Player::Instance().Update();
        BoostManager::Update(Player::Instance());   
        FireballManager::RemoveOutOfBoundFireballs();
        EnemyManager::Update();
        ItemManager::Update();
       
        ItemSpawn();

        auto& fireballs = FireballManager::GetFireballs();
        for (auto it = fireballs.begin(); it != fireballs.end();) {
            bool hit = false;
            for (auto& e : EnemyManager::GetEnemies()) {
                if (CheckCollisionRecs(it->GetHitbox(), e->GetHitbox())) {
                    e->TakeDamage(it->GetDamage());
                    PlaySound(SFX::goblinHurt);
                    it = fireballs.erase(it);
                    hit = true;
                    break;
                }
            }
            if (!hit) ++it;
        }

        BeginDrawing();

            ClearBackground(BLACK);
            DrawTexture(background, 0, 0, WHITE);
            Player::Instance().DrawPlayer();
            ItemManager::Draw();
            FireballManager::Draw();
            EnemyManager::Draw();
            WallManager::Draw();

        EndDrawing();
    }


    StopMusicStream(SFX::bgMusic);
    ItemTexture::UnloadItemTexture();
    SFX::UnloadSFX();
    VerticalWall::UnloadWallTexture();
    HorizontalWall::UnloadWallTexture();
    EnemyManager::Destruct();
    PlayerTexture::UnloadTextures();
    Fireball::UnloadFireballTexture();
    WallManager::Destruct();
    BoostManager::Destruct();
    CloseAudioDevice();
    CloseWindow();
}