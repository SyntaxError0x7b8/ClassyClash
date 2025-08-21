//
// Created by qos on 8/12/25.
//

#include "prop.h"
#include "raymath.h"

Prop::Prop(const Vector2 position, const Texture2D prpTexture) :
                worldPos(position),
                texture(prpTexture){
}

Prop::~Prop() {
    UnloadTexture(texture);
}

void Prop::render(const Vector2 knightMapPos) const {
    const Vector2 screenPos = Vector2Subtract(worldPos, knightMapPos);
    DrawTextureEx(texture, screenPos, 0.0f, scale, WHITE);

    // debug prop collision rectangle
    /*DrawRectangleLines(
                    static_cast<int>(screenPos.x) + 5,
                    static_cast<int>(screenPos.y) + 5,
                    static_cast<int>(texture.width) * static_cast<int>(scale) - 5,
                    static_cast<int>(texture.height) * static_cast<int>(scale) - 5
                    , RED);
                    */

}

Rectangle Prop::getCollisionRectangle(const Vector2 knightMapPos) const {
    Vector2 screenPos = Vector2Subtract(worldPos, knightMapPos);
    const float padding = 5.0f;
    return Rectangle{
        screenPos.x + padding,
        screenPos.y + padding,
        (static_cast<float>(texture.width) * scale) - padding,
        (static_cast<float>(texture.height) * scale) - padding,
    };
}
