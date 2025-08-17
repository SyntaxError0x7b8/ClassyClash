//
// Created by qos on 8/14/25.
//

#include "enemy.h"

Enemy::Enemy() = default;

Enemy::Enemy(const Vector2 pos, Texture2D idleText, Texture2D runText)
{
    worldPos = pos;
    idle = idleText;
    run = runText;
    texture = idleText;
    width = static_cast<float>(texture.width) / static_cast<float>(maxFrames);
    height = static_cast<float>(texture.height);
    scale = 4.0f;
}

Enemy::~Enemy() {
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}


void Enemy::tick(const float deltaTime) {
    // call base class function only (for now)
    BaseCharacter::tick(deltaTime);
}

