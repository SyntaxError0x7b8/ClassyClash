//
// Created by qos on 8/14/25.
//

#ifndef CLASSYCLASH_ENEMY_H
#define CLASSYCLASH_ENEMY_H

#include "baseCharacter.h"


class Enemy : public BaseCharacter {
public:
    Enemy();

    Enemy(Vector2 pos, Texture2D idleText, Texture2D runText);

    ~Enemy();

    void tick(float deltaTime) override;

    void setTarget(BaseCharacter* knightTarget) { target = knightTarget;}

    [[nodiscard]] Vector2 getScreenPos() override;


private:

    BaseCharacter *target{};

};


#endif //CLASSYCLASH_ENEMY_H