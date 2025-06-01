#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"

using namespace std;

int main () { 

    const int SCREEN_WIDTH = 1440;
    const int SCREEN_HEIGHT = 900;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My first RAYLIB program!");
    SetTargetFPS(60);

    PlayerTexture::LoadTextures();
    Fireball::LoadFireballTexture();
    GoblinTexture::LoadGoblinTextures();

    Goblin g;
    while (WindowShouldClose() == false){
        Player::Instance().Update();
        FireballManager::RemoveOutOfBoundFireballs();
        BeginDrawing();
            ClearBackground(BLACK);
            Player::Instance().DrawPlayer();
            FireballManager::Draw();
            g.Draw();
        EndDrawing();
    }

    PlayerTexture::UnloadTextures();
    Fireball::UnloadFireballTexture();
    CloseWindow();
} 