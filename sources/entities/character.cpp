//
// Created by qos on 8/10/25.
//

#include "character.h"
#include "raymath.h" // raymath.h to be included AFTER raylib to avoid conflict with definitions

Character::Character(const int winW, const int winH, const float mapScale = 1) {
    width = static_cast<float>(texture.width) / static_cast<float>(maxFrames);
    height = static_cast<float>(texture.height);
    scale = mapScale;
    screenPos = {
        static_cast<float>(winW)/2.0f - (scale * (0.5f * width)),
        static_cast<float>(winH)/2.0f - (scale * (0.5f * height))
    };
}


Character::~Character() {
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}


void Character::tick(float const deltaTime) {
    // enable undo movement
    worldPosLastFrame = worldPos;
    // movement direction
    Vector2 direction {};
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
        // sprite is knightIdle
        texture = idle;
    }
    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame = (++frame) % maxFrames;
        runningTime = 0.0f;
    }
}

void Character::drawKnight() const {
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

void Character::undoMovement() {
    worldPos = worldPosLastFrame;
}

Rectangle Character::getCollisionRectangle() const {
    constexpr float padding = 10.0f;
    return Rectangle{
        screenPos.x + padding,
        screenPos.y + padding,
        (static_cast<float>(texture.width) / static_cast<float>(maxFrames) * scale) - padding,
        (static_cast<float>(texture.height) * scale) - padding,
    };
}