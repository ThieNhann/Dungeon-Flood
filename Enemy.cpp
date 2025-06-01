#include "Enemy.h"

Texture GoblinTexture::goblinDown;
Texture GoblinTexture::goblinUp;
Texture GoblinTexture::goblinLeft;
Texture GoblinTexture::goblinRight;

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
    DrawTexture(texture.GetCurrentTexture(facing),hitbox.x, hitbox.y, WHITE);
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
    float t = GetFrameTime();
    hitbox.x += direction.x * speed * t;
    hitbox.y += direction.y * speed * t;
}