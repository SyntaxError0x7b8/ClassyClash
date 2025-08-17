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

Rectangle BaseCharacter::getCollisionRectangle() const {
    constexpr float padding = 10.0f;
    return Rectangle{
        screenPos.x + padding,
        screenPos.y + padding,
        (static_cast<float>(texture.width) / static_cast<float>(maxFrames) * scale) - padding,
        (static_cast<float>(texture.height) * scale) - padding,
    };
}

void BaseCharacter::draw() const {
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

void BaseCharacter::tick(const float deltaTime) {
    // enable undo movement
    worldPosLastFrame = worldPos;

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame = (++frame) % maxFrames;
        runningTime = 0.0f;
    }
}

