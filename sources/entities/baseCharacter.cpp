//
// Created by qos on 8/16/25.
//

#include "baseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() = default;
BaseCharacter::~BaseCharacter() {
    UnloadTexture(texture);
    UnloadTexture(run);
    UnloadTexture(idle);
}

void BaseCharacter::undoMovement() {
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRectangle() {
    constexpr float padding = 10.0f;
    return Rectangle{
        getScreenPos().x + padding,
        getScreenPos().y + padding,
        (static_cast<float>(texture.width) / static_cast<float>(maxFrames) * scale) - padding,
        (static_cast<float>(texture.height) * scale) - padding,
    };
}

void BaseCharacter::draw() {
    if (!getAlive()) { return;}
    const Rectangle source {
        (static_cast<float>(frame) * width),
        0.0f,
        rightLeft * width,
        height
    };
    const Rectangle dest {
        getScreenPos().x,
        getScreenPos().y,
        scale * width,
        scale * height
    };
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}

void BaseCharacter::tick(const float deltaTime) {
    if (!getAlive()) { return;}
    // enable undo movement
    worldPosLastFrame = worldPos;

    // handle common movement functionality
    if (Vector2Length(velocity) != 0.0f) { // beware of float comparison
        // select animation sprite when moving
        texture = run;
        // set worldPos = worlPos + direction (change character pos in world map)
        velocity = Vector2Scale(Vector2Normalize(velocity), speed);
        worldPos = Vector2Add(worldPos, velocity);
        rightLeft = (velocity.x < 0.0f) ? -1.0f : 1.0f;
    }
    else {
        // sprite is knightIdle
        texture = idle;
    }
    velocity = {};

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame = (++frame) % maxFrames;
        runningTime = 0.0f;
    }
}

