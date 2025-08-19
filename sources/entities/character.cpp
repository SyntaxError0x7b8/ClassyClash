//
// Created by qos on 8/10/25.
//

#include "character.h"
#include "raymath.h" // raymath.h to be included AFTER raylib to avoid conflict with definitions

Character::Character(const int winW, const int winH, const float mapScale = 1) :
    winWidth(winW), winHeight(winH){
    idle = LoadTexture("../assets/characters/knight_idle_spritesheet.png") ;
    run = LoadTexture("../assets/characters/knight_run_spritesheet.png");
    texture = idle;
    width = static_cast<float>(texture.width) / static_cast<float>(maxFrames);
    height = static_cast<float>(texture.height);
    scale = mapScale; // cannot use initialiser list because it is a BaseCharacter member

}


Character::~Character() {
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}


void Character::tick(const float deltaTime) {
    // movement direction
    if (IsKeyDown(KEY_A)) { velocity.x--; }
    if (IsKeyDown(KEY_D)) { velocity.x++; }
    if (IsKeyDown(KEY_S)) { velocity.y++; }
    if (IsKeyDown(KEY_W)) { velocity.y--; }

    // call base class function after velocity is updated
    BaseCharacter::tick(deltaTime);


}

Vector2 Character::getScreenPos() {
    return Vector2 {static_cast<float>(winWidth)/2.0f - (scale * (0.5f * width)),
                    static_cast<float>(winHeight)/2.0f - (scale * (0.5f * height))};

}

