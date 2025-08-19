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
    speed = 3.0f;
}

Enemy::~Enemy() {
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}


void Enemy::tick(const float deltaTime) {
    // get toTarget i.e. knight's location Target = Knight - Enemy
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);
    // normalise vector to target
    Vector2 direction = Vector2Normalize(toTarget);
    // multiply normalised vector by the enemy's speed
    direction = Vector2Scale(direction, speed);
    // move enemy in the target's direction (i.e. set worldPos)
    worldPos = Vector2Add(worldPos, direction);
    // target value must be set before calling Enemy::tick()
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());

    // call base class function
    BaseCharacter::tick(deltaTime);



}

