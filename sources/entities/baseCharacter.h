//
// Created by qos on 8/16/25.
//

#ifndef CLASSYCLASH_BASECHARACTER_H
#define CLASSYCLASH_BASECHARACTER_H

#include "raylib.h"


class BaseCharacter {
    public:
    BaseCharacter();

    ~BaseCharacter();

    [[nodiscard]] Vector2 getWorldPos() const { return worldPos;}

    void undoMovement(); // perfect example of function to be replaced by "Command" design pattern

    [[nodiscard]] Rectangle getCollisionRectangle();

    virtual void draw();

    virtual void tick(float deltaTime);

    virtual Vector2 getScreenPos() = 0; // it makes BaseCharacter an Abstract Class; i.e. no instances.

protected:
    Texture2D idle {};

    Texture2D run {};

    Texture2D texture {};


    Vector2 worldPos {};

    // +1: Facing right; -1: Facing right
    float rightLeft {1.0f};

    // animation variables
    float runningTime {};

    int frame {};

    int maxFrames {6};

    const float updateTime {1.0f/12.0f};

    float speed {4.0f};

    float scale {4.0f};

    float width {};

    float height {};

    Vector2 worldPosLastFrame {};

    Vector2 velocity {};

};


#endif //CLASSYCLASH_BASECHARACTER_H