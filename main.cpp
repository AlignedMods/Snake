#include <iostream>
#include <raylib.h>

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Food {

    public:
    Vector2 position = {5,6};

    void Draw() 
    {
        DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, darkGreen);
    }

};

int main() {

    InitWindow(cellSize * cellCount, cellSize * cellCount, "game");
    SetTargetFPS(60);

    Food food = Food();

    while (WindowShouldClose() == !true) 
    {
        BeginDrawing();

        ClearBackground(green);
        food.Draw();

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}