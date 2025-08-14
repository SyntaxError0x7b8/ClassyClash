//
// Created by qos on 8/12/25.
//

#ifndef CLASSYCLASH_PROP_H
#define CLASSYCLASH_PROP_H

#include "raylib.h"

class Prop {
public:
    Prop()=default;

    Prop(Vector2 position, Texture2D prpTexture);

    ~Prop();

    void render(Vector2 knightMapPos) const;

    [[nodiscard]] Rectangle getCollisionRectangle(Vector2 knightMapPos) const;

private:
    Vector2 worldPos {};

    Texture2D texture{};

    float scale {4.0f};
};


#endif //CLASSYCLASH_PROP_H