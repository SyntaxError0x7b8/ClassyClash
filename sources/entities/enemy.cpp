//
// Created by qos on 8/14/25.
//

#include "enemy.h"
#include "raymath.h"

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
    // target value must be set before calling Enemy::tick()
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    // call base class function
    BaseCharacter::tick(deltaTime);

}

