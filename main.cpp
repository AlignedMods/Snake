#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool elementInDeck(Vector2 element, deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals( deque[i], element))
        {
            return true;
        }
    }
    return false;
}

bool eventTriggered(double interval)
{
    double currentTime = GetTime();

    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{
    public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1,0};
    bool addSegment = false;

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x;
            float y = body[i].y;

            Rectangle segment = Rectangle{x * cellSize, y * cellSize, (float)cellSize, (float)cellSize};

            DrawRectangleRounded(segment,0.6, 6, darkGreen);
        }
    }

    void Update()
    {
        if (addSegment == true)
        {
            body.push_front(Vector2Add(body[0], direction));
            addSegment = false;
        }
        else
        {
            body.pop_back();
            body.push_front(Vector2Add(body[0], direction));
        } 
    }

    void Reset()
    {
        body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
        direction = {1,0};
    }

};

class Food 
{

    public:
    Vector2 position;
    Texture2D texture;

    Food(deque<Vector2> snakeBody)
    {
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = generateRandomPos(snakeBody);
    }

    ~Food() 
    {
        UnloadTexture(texture);
    }

    void Draw() 
    {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    Vector2 generateRandomCell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }
    
    Vector2 generateRandomPos(deque<Vector2> snakeBody)
    {

        Vector2 position = generateRandomCell();

        while (elementInDeck(position, snakeBody))
        {
            position = generateRandomCell();
        }
        return position;
    }

};

class Game 
{
    public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        if (running == true)
        {
            snake.Update();
            CheckCollsionWithFood();
            CheckCollisonsWithEdges();
            CheckCollisionsWithTail();
        }
    }

    void CheckCollsionWithFood()
    {
        if(Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.generateRandomPos(snake.body);
            snake.addSegment = true;
        }
    }

    void CheckCollisonsWithEdges()
    {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1)
        {
            GameOver();
        }
        if (snake.body[0].y == cellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    void GameOver()
    {
        snake.Reset();
        food.position = food.generateRandomPos(snake.body);
        running = false;
    }

    void CheckCollisionsWithTail()
    {
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if (elementInDeck(snake.body[0], headlessBody))
        {
            GameOver();
        }
    }

};

int main() {

    InitWindow(cellSize * cellCount, cellSize * cellCount, "game");
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == !true) 
    {
        BeginDrawing();

        if (eventTriggered(0.2))
        {
            game.Update();
        }

        if (IsKeyPressed(KEY_W) && game.snake.direction.y != 1)
        {
            game.running = true;
            game.snake.direction = {0, -1};
        }

        if (IsKeyPressed(KEY_S) && game.snake.direction.y != -1)
        {
            game.running = true;
            game.snake.direction = {0, 1};
        }

        if (IsKeyPressed(KEY_A) && game.snake.direction.x != 1)
        {
            game.running = true;
            game.snake.direction = {-1, 0};
        }

        if (IsKeyPressed(KEY_D) && game.snake.direction.x != -1)
        {
            game.running = true;
            game.snake.direction = {1, 0};
        }

        ClearBackground(green);
        game.Draw();

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}