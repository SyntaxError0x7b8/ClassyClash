/**
 * Program created following tutorial:
 * "C++ Fundamentals: Learn Game Programming For Beginners"
 * source: www.gamedev.tv/courses/cpp-fundamentals/
 * @version 2025-08-13
 *
 * */



#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"

#include "character.h"
#include "prop.h"
#include "enemy.h"


// temporary placed here class


int main() {
    constexpr int windowWidth = 384;
    constexpr int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "RPG Game");

    const Texture2D openMap = LoadTexture("../assets/nature_tileset/OpenWorldAutumn24x24.png");
    constexpr float mapScale {4.0f};


    // Main Character (knight). Should be singleton
    Character knight {windowWidth, windowHeight, mapScale};

    // props
    const Prop props[2] {
        Prop{Vector2{600.0f, 300.0f}, LoadTexture("../assets/nature_tileset/Rock.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("../assets/nature_tileset/Log.png")}
    };

    // enemy
    Enemy goblin({300.0f, 300.0f},
        LoadTexture("../assets/characters/goblin_idle_spritesheet.png"),
        LoadTexture("../assets/characters/goblin_run_spritesheet.png"));




    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        /*************************
         * SET UP / INPUT SECTION
         * ***********************/
        // seconds  per frame
        const float dT = GetFrameTime();
        // position of the map relative to the knight
        const Vector2 mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);


        /************************
         * UPDATE SECTION
         * **********************/
        goblin.setTarget(&knight);

        knight.tick(dT);
        goblin.tick(dT);

        // check map bounds
        if (knight.getWorldPos().x < 0.0f ||
            knight.getWorldPos().y < 0.0f ||
            knight.getWorldPos().x + windowHeight >= static_cast<float>(openMap.width) * mapScale||
            knight.getWorldPos().y + windowHeight >= static_cast<float>(openMap.height) * mapScale) {
            // undo
            knight.undoMovement();
        }
        // check collision with props
        for (auto &prop : props) {
            if (CheckCollisionRecs(knight.getCollisionRectangle(),prop.getCollisionRectangle(knight.getWorldPos()))) {
                knight.undoMovement();
            }
            if (CheckCollisionRecs(goblin.getCollisionRectangle(),prop.getCollisionRectangle(goblin.getWorldPos()))) {
                goblin.undoMovement();
            }
        }

        // check for attack collisions
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            goblin.setAlive(!CheckCollisionRecs(goblin.getCollisionRectangle(), knight.getWeaponCollisionRect()));
        }

        /***********************
         * DRAWING SECTION
         * *********************/

        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Background map moves in the opposite direction to knight's position

        DrawTextureEx(openMap, mapPos, 0, mapScale, WHITE);

        // draw props in array
        for (auto &prop : props) { // no need to copy the prop, use a reference
            prop.render(knight.getWorldPos());
        }

        // draw knight's health value
        if ( !knight.getAlive()) {
            // character is not alive: Game Over!
            DrawText("Game Over!", 55.0f, 45.0f, 40, RED);
            EndDrawing(); // no need to draw anything else
            continue; // re-start the look but it will always end here unless we somehow enable re-start the game
        }
        else {
            // character alive and kicking
            std::string healthDisplay = "Health: ";
            int intHealth = static_cast<int>(std::round(knight.getHealth())); // I prefer health to be an integer
            std::string knightHealth = std::to_string(intHealth);
            healthDisplay.append(knightHealth, 0, 3); // only 3 characters. Handy if use of float (change to 4 or 5)
            DrawText(healthDisplay.c_str(), 55.0f, 45.0f, 40, RED);
        }

        // draw knight and enemies
        knight.draw();
        knight.drawSword();

        goblin.draw();



        EndDrawing();
    }

    UnloadTexture(openMap);


    return 0;
}