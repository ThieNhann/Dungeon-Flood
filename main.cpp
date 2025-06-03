#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Wall.h"
#include "SFX.h"
#include "Items.h"
#include "Icon.h"
using namespace std;

int main () { 

    const int SCREEN_WIDTH = ::SCREEN_WIDTH;
    const int SCREEN_HEIGHT = ::SCREEN_HEIGHT;

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
    IconTexture::LoadIconTexture();

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
            for (int i = 0; i < Player::Instance().GetHealth(); ++i) {
                DrawTexture(IconTexture::heart, HEART_ICON_X + i * HEART_ICON_SPACING, HEART_ICON_Y, WHITE);
            }
            
        EndDrawing();
    }


    StopMusicStream(SFX::bgMusic);
    
    // Cleanup managers first
    ItemManager::Destruct();
    EnemyManager::Destruct(); 
    FireballManager::Destruct(); // Add this
    BoostManager::Destruct();
    WallManager::Destruct();

    // Then unload resources
    IconTexture::UnloadIconTexture();
    ItemTexture::UnloadItemTexture();
    SFX::UnloadSFX();
    VerticalWall::UnloadWallTexture();
    HorizontalWall::UnloadWallTexture();
    Fireball::UnloadFireballTexture();
    PlayerTexture::UnloadTextures();
    UnloadTexture(background);

    CloseAudioDevice();
    CloseWindow();
}