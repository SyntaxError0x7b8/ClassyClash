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
    if (!getAlive()) { return;}
    // movement direction
    if (IsKeyDown(KEY_A)) { velocity.x--; }
    if (IsKeyDown(KEY_D)) { velocity.x++; }
    if (IsKeyDown(KEY_S)) { velocity.y++; }
    if (IsKeyDown(KEY_W)) { velocity.y--; }

    // reset attach
    setAttack(false);
    // check if attack in progress
    setAttack(IsMouseButtonDown(MOUSE_BUTTON_LEFT));

    // call base class function after velocity is updated
    BaseCharacter::tick(deltaTime);


}

Vector2 Character::getScreenPos() {
    return Vector2 {static_cast<float>(winWidth)/2.0f - (scale * (0.5f * width)),
                    static_cast<float>(winHeight)/2.0f - (scale * (0.5f * height))};

}

void Character::drawSword() {
    if (!getAlive()) { return;}
    Vector2 origin{};
    Vector2 offsetSword{};
    float rotation {};
    if (rightLeft > 0.0f) {
        origin = {0.0f, static_cast<float>(weapon.height) * scale};
        offsetSword = {40.0f, 50.0f}; // trial and error
        rotation = attacking()? 35.0f : 0.0f;
        weaponCollisionRect = {
            getScreenPos().x + offsetSword.x,
            getScreenPos().y + offsetSword.y - static_cast<float>(weapon.height) * scale,
            static_cast<float>(weapon.width) * scale,
            static_cast<float>(weapon.height) * scale
        };
    }
    else {
        origin = {static_cast<float>(weapon.width) * scale, static_cast<float>(weapon.height) * scale};
        offsetSword = {25.0f, 50.0f}; // trial and error
        rotation = attacking()? -35.0f : 0.0f;;
        weaponCollisionRect = {
            getScreenPos().x + offsetSword.x - static_cast<float>(weapon.width) * scale,
            getScreenPos().y + offsetSword.y - static_cast<float>(weapon.height) * scale,
            static_cast<float>(weapon.width) * scale,
            static_cast<float>(weapon.height) * scale
        };
    }
    const Rectangle source {0.0f, 0.0f,
                    static_cast<float>(weapon.width) * rightLeft, static_cast<float>(height)};
    const Rectangle dest {getScreenPos().x + offsetSword.x, getScreenPos().y + offsetSword.y,
                    scale * static_cast<float>(weapon.width), scale * static_cast<float>(weapon.height)};
    DrawTexturePro(weapon, source, dest, origin,rotation, WHITE);

    // debug weapon collision rectangle
    DrawRectangleLines(
                    weaponCollisionRect.x,
                    weaponCollisionRect.y,
                    weaponCollisionRect.width,
                    weaponCollisionRect.height
                    , RED);
}

