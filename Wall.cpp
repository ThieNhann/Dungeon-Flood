#include "Wall.h" 

Texture VerticalWall::texture;
Texture HorizontalWall::texture;
std::vector<RectWall*> WallManager::walls;

VerticalWall::VerticalWall(Vector2 pos) {
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.height = 350;
    hitbox.width = 50;
}

void VerticalWall::Draw() {
    DrawTexture(texture, hitbox.x, hitbox.y, WHITE);
}

void VerticalWall::LoadWallTexture() {
    texture = LoadTexture("resources/images/verticalWall.png");
}

void VerticalWall::UnloadWallTexture() {
    UnloadTexture(texture);
}


HorizontalWall::HorizontalWall(Vector2 pos) {
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.height = 50;
    hitbox.width = 620;
}

void HorizontalWall::Draw() {
    DrawTexture(texture, hitbox.x, hitbox.y, WHITE);
}

void HorizontalWall::LoadWallTexture() {
    texture = LoadTexture("resources/images/horizontalWall.png");
}

void HorizontalWall::UnloadWallTexture() {
    UnloadTexture(texture);
}

void WallManager::InitCornerWalls() {
    walls.clear();
    walls.emplace_back(new HorizontalWall({0, 0}));
    walls.emplace_back(new VerticalWall({0, 0}));
    walls.emplace_back(new VerticalWall({0, 500}));
    walls.emplace_back(new HorizontalWall({820, 0}));
    walls.emplace_back(new VerticalWall({1390, 0}));
    walls.emplace_back(new VerticalWall({1390, 500}));
    walls.emplace_back(new HorizontalWall({0, 850}));
    walls.emplace_back(new HorizontalWall({820, 850}));
}

void WallManager::Draw() {
    for (auto& w : walls) w->Draw();
}

std::vector<RectWall*>& WallManager::GetWalls() {
    return walls;
}

void WallManager::Destruct() {
    for (auto& w : walls) {
        delete w;
    }
} 