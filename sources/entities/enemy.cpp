//
// Created by qos on 8/14/25.
//

#include "enemy.h"
#include "raymath.h"

Enemy::Enemy(const Vector2 pos, Texture2D idleText, Texture2D runText) :
        worldPos(pos),
        texture(idleText),
        idle(idleText),
        run(runText)
{
    width = static_cast<float>(texture.width) / static_cast<float>(maxFrames);
    height = static_cast<float>(texture.height);
    scale = 4.0f;
}

Enemy::~Enemy() {
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}


void Enemy::tick(float const deltaTime) {
    // enable undo movement
    worldPosLastFrame = worldPos;
    // movement direction
    /*Vector2 direction {};
    if (IsKeyDown(KEY_A)) {  direction.x--; }
    if (IsKeyDown(KEY_D)) { direction.x++; }
    if (IsKeyDown(KEY_S)) { direction.y++; }
    if (IsKeyDown(KEY_W)) { direction.y--; }
    // check if we need to move
    if (Vector2Length(direction) != 0.0f) { // beware of float comparison
        // select animation sprite when moving
        texture = run;
        // set worldPos = worlPos + direction (change character pos in world map)
        const Vector2 movement = Vector2Scale(Vector2Normalize(direction), speed);
        worldPos = Vector2Add(worldPos, movement);
        rightLeft = (direction.x < 0.0f) ? -1.0f : 1.0f;
    }
    else {
        // sprite is Idle
        texture = idle;
    }*/
    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame = (++frame) % maxFrames;
        runningTime = 0.0f;
    }
}

void Enemy::drawGoblin() const {
    const Rectangle source {
        (static_cast<float>(frame) * width),
        0.0f,
        rightLeft * width,
        height
    };
    const Rectangle dest {
        screenPos.x,
        screenPos.y,
        scale * width,
        scale * height
    };
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}

void Enemy::undoMovement() {
    worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCollisionRectangle() const {
    constexpr float padding = 10.0f;
    return Rectangle{
        screenPos.x + padding,
        screenPos.y + padding,
        (static_cast<float>(texture.width) / static_cast<float>(maxFrames) * scale) - padding,
        (static_cast<float>(texture.height) * scale) - padding,
    };
}