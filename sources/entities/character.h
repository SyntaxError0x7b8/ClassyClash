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



private:

};



#endif //CLASSYCLASH_CHARACTER_H