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



private:
    int winWidth {};
    int winHeight {};

};



#endif //CLASSYCLASH_CHARACTER_H