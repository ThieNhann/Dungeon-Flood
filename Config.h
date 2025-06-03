#ifndef CONFIG_H
#define CONFIG_H

enum Direction {UP, DOWN, LEFT, RIGHT};

// Screen
const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 900;

// Player
const int PLAYER_SPEED = 200;
const int PLAYER_HEALTH = 3;
const float PLAYER_FIRE_COOLDOWN = 0.35f;
const float PLAYER_INVINCIBLE_TIME = 3.0f;
const float PLAYER_WIDTH = 40.0f;
const float PLAYER_HEIGHT = 40.0f;
const float PLAYER_START_X = 720.0f;
const float PLAYER_START_Y = 450.0f;

// Enemy
const int GOBLIN_SPEED = 160;
const int GOBLIN_HEALTH = 1;
const float GOBLIN_WIDTH = 35.0f;
const float GOBLIN_HEIGHT = 35.0f;
const float GOBLIN_SEPARATION_RADIUS = 10.0f;
const float GOBLIN_CHASE_WEIGHT = 1.0f;
const float GOBLIN_SEPARATION_WEIGHT = 1.2f;

const int MUSHROOM_SPEED = 110;
const int MUSHROOM_HEALTH = 3;
const float MUSHROOM_WIDTH = 50.0f;
const float MUSHROOM_HEIGHT = 50.0f;

// Fireball
const int FIREBALL_SPEED = 300;
const float FIREBALL_WIDTH_H = 32.0f;
const float FIREBALL_HEIGHT_H = 20.0f;
const float FIREBALL_WIDTH_V = 20.0f;
const float FIREBALL_HEIGHT_V = 32.0f;
const int FIREBALL_DAMAGE = 1;

// Wall
const float VERTICAL_WALL_WIDTH = 50.0f;
const float VERTICAL_WALL_HEIGHT = 350.0f;
const float HORIZONTAL_WALL_WIDTH = 620.0f;
const float HORIZONTAL_WALL_HEIGHT = 50.0f;

// Item
const float ITEM_WIDTH = 32.0f;
const float ITEM_HEIGHT = 32.0f;
const float ITEM_DESPAWN_TIME = 7.5f;
const float ITEM_SPAWN_MIN_TIME = 10.0f;
const float ITEM_SPAWN_MAX_TIME = 20.0f;

// Boost
const float BOOST_DURATION = 10.0f;
const float FIRESPEEDBOOST_COOLDOWN_FACTOR = 0.5f;

// Heart icon
const float HEART_ICON_X = 60.0f;
const float HEART_ICON_Y = 60.0f;
const float HEART_ICON_SPACING = 40.0f;

// Heart protection icon offset
const float HEART_PROTECTION_OFFSET_X = 30.0f;
const float HEART_PROTECTION_OFFSET_Y = -20.0f;

// Multishot fireball offset
const float MULTISHOT_OFFSET_X1 = 15.0f;
const float MULTISHOT_OFFSET_Y1 = -20.0f;
const float MULTISHOT_OFFSET_Y2 = 40.0f;
const float MULTISHOT_OFFSET_X2 = 45.0f;
const float MULTISHOT_OFFSET_X3 = -15.0f;
const float MULTISHOT_OFFSET_Y3 = 10.0f;

// Enemy spawn
const float ENEMY_SPAWN_INTERVAL = 5.0f;
const float ENEMY_SPAWN_WIDTH = 45.0f;
const float ENEMY_SPAWN_HEIGHT = 45.0f;
const int ENEMY_SPAWN_WAVE_MAX = 7;

#endif