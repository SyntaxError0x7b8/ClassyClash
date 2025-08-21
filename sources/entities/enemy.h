//
// Created by qos on 8/14/25.
//

#ifndef CLASSYCLASH_ENEMY_H
#define CLASSYCLASH_ENEMY_H

#include "character.h"


class Enemy : public BaseCharacter {
public:
    Enemy();

    Enemy(Vector2 pos, Texture2D idleText, Texture2D runText);

    ~Enemy();

    void tick(float deltaTime) override;

    void setTarget(Character* knightTarget) { target = knightTarget;}

    [[nodiscard]] Vector2 getScreenPos() override;


private:

    Character *target{};

    float damagePerSecond {10.0f};

};


#endif //CLASSYCLASH_ENEMY_H