//
// Created by qos on 8/10/25.
//

#include "character.h"
#include "raymath.h" // raymath.h to be included AFTER raylib to avoid conflict with definitions

Character::Character(const int winW, const int winH, const float mapScale = 1) {
    idle = LoadTexture("../assets/characters/knight_idle_spritesheet.png") ;
    run = LoadTexture("../assets/characters/knight_run_spritesheet.png");
    texture = idle;
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


void Character::tick(const float deltaTime) {
    // call base class function
    BaseCharacter::tick(deltaTime);
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

}

