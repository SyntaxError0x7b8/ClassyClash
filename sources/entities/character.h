//
// Created by qos on 8/10/25.
//

#ifndef CLASSYCLASH_CHARACTER_H
#define CLASSYCLASH_CHARACTER_H

#include "baseCharacter.h"



class Character : public BaseCharacter{
public:
    Character(int winW, int winH, float mapScale);

    ~Character();

    void tick(float deltaTime) override;

    [[nodiscard]] Vector2 getScreenPos() override;

    void drawSword();

    [[nodiscard]] bool attacking() const { return attack;}

    void setAttack(const bool attackAdversary) {attack = attackAdversary;}

    [[nodiscard]] Rectangle getWeaponCollisionRect() { return weaponCollisionRect;}

private:
    int winWidth {};

    int winHeight {};

    Texture2D weapon{LoadTexture("../assets/characters/weapon_sword.png")};

    Rectangle weaponCollisionRect{};

    bool attack {};
};



#endif //CLASSYCLASH_CHARACTER_H