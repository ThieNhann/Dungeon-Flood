#include "Utils.h"

bool IsWASDPressed() {
    return (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_S));
}

