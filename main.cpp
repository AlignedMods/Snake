#include <iostream>
#include <raylib.h>

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

int main() {

    const int width = 750;
    const int height = 750;

    InitWindow(cellSize * cellCount, cellSize * cellCount, "game");
    SetTargetFPS(60);

    while (WindowShouldClose() == !true) 
    {
        BeginDrawing();

        ClearBackground(green);

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}