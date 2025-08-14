//
// Created by qos on 8/10/25.
//

#ifndef CLASSYCLASH_CHARACTER_H
#define CLASSYCLASH_CHARACTER_H

#include "raylib.h"


class Character {
public:
    Character(int winW, int winH, float mapScale);
    ~Character();
    [[nodiscard]] Vector2 getWorldPos() const { return worldPos;}
    void tick(float deltaTime);
    void drawKnight() const;
    void undoMovement(); // perfect example of function to be replaced by "Command" design pattern
    [[nodiscard]] Rectangle getCollisionRectangle() const;

private:
    const Texture2D idle {LoadTexture("../assets/characters/knight_idle_spritesheet.png")};
    const Texture2D run {LoadTexture("../assets/characters/knight_run_spritesheet.png")};
    Texture2D texture {idle}; // probably references or pointers is more efficient
    Vector2 screenPos {};
    Vector2 worldPos {};
    // +1: Facing right; -1: Facing right
    float rightLeft {1.0f};
    // animation variables
    float runningTime {};
    int frame {};
    int maxFrames {6};
    const float updateTime {1.0f/12.0f};
    const float speed {4.0f};
    float scale;
    float width {};
    float height {};
    Vector2 worldPosLastFrame {};

};



#endif //CLASSYCLASH_CHARACTER_H