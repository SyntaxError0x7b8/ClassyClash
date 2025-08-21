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
    if (!getAlive()) { return;}

    // get toTarget i.e. knight's location Target = Knight - Enemy
    if ( CheckCollisionRecs(target->getCollisionRectangle(),this->getCollisionRectangle())) {
        // enemy and knight already overlap
        velocity = {0.0f, 0.0f}; // stop moving once they collide
    }
    else {
        velocity = Vector2Subtract(target->getScreenPos(), this->getScreenPos()); // move towards the knight
    }

    // call base class function
    BaseCharacter::tick(deltaTime);

    // cause damage
    if ( CheckCollisionRecs(target->getCollisionRectangle(),this->getCollisionRectangle())) {
        // reduce taget's health
        target->takeDamage(damagePerSecond * deltaTime);
    }




}

Vector2 Enemy::getScreenPos() {
    return Vector2Subtract(worldPos, target->getWorldPos());
}

