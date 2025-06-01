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
    hitbox.width = 64;
    hitbox.height = 64;
    hitbox.x = 720;
    hitbox.y = 450;
    speed = 200;
    texture.LoadTextures();
}

Player& Player::Instance() {
    static Player instance;
    return instance;
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

    if (IsKeyDown(KEY_W)) {
        SetDirection(UP);
        hitbox.y -= t * speed;  
    }
    if (IsKeyDown(KEY_S)) {
        SetDirection(DOWN);
        hitbox.y += t * speed;
    }
    if (IsKeyDown(KEY_D)) {
        SetDirection(RIGHT); 
        hitbox.x += t * speed;
    }
    if (IsKeyDown(KEY_A)) {
        SetDirection(LEFT);
        hitbox.x -= t * speed;
    }

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
    if (fire) {
        Fireball fireball({hitbox.x, hitbox.y}, fireDirection);
        FireballManager::AddFireball(fireball);
    }
}

Direction Player::GetDirection() {
    return direction;
}

void Player::SetDirection(Direction drt) {
    direction = drt;
}