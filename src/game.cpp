#include "game.h"
#include <GLFW/glfw3.h>


void Game::Init() {
    field.Init();
    currentShape.X = 3;
    currentShape.Y = 0;

    field.WithShape(currentShape);
}

void Game::Render(float dt) {
    field.Render();
}


bool Game::isKeyPressed(int key, float time, float cd = 0.2, float cds = 0.03) {
    if (Keys[key]) {
        if ( KeyProcessedAt[key] < KeyPressedSince[key] )
        {
            KeyProcessedAt[key] = time;
            return true;
        }

        if (time - KeyPressedSince[key] < cd) {
            return false;
        }

        if (time - KeyProcessedAt[key] < cds) {
            return false;
        }

        KeyProcessedAt[key] = time;
        return true;
    }
    return false;
}

void Game::Update(float time) {
    if (time - lastMoveTime > 0.5) {

        if (field.IsValidShape(currentShape, currentShape.X, currentShape.Y + 1)) {
            field.WithShape(currentShape);
            currentShape.Y++;
            field.WithShape(currentShape);
        } else {
            field.FreezeShape(currentShape);



            currentShape.X = 3;
            currentShape.Y = 0;
            currentShape.Random();

            field.WithShape(currentShape);
            if ( Keys[GLFW_KEY_DOWN] )
            {
                KeyPressedSince[GLFW_KEY_DOWN] = time;
            }
        }

        lastMoveTime = time;
    }

    if ( isKeyPressed(GLFW_KEY_LEFT, time)  )
    {
        if (field.IsValidShape(currentShape, currentShape.X-1, currentShape.Y)) {
            field.WithShape(currentShape);
            currentShape.X--;
            field.WithShape(currentShape);
        }
    } else if ( isKeyPressed(GLFW_KEY_RIGHT, time) )
    {
        if (field.IsValidShape(currentShape, currentShape.X+1, currentShape.Y)) {
            field.WithShape(currentShape);
            currentShape.X++;
            field.WithShape(currentShape);
        }
    } else if ( isKeyPressed(GLFW_KEY_DOWN, time, 0.1, 0.01) )
    {
        if (field.IsValidShape(currentShape, currentShape.X, currentShape.Y+1)) {
            field.WithShape(currentShape);
            currentShape.Y++;
            field.WithShape(currentShape);
        }
    } else if ( isKeyPressed(GLFW_KEY_UP, time, 0.2f, 0.15f) )
    {
        Shape nextShape = currentShape.Rotate();
        if (field.IsValidShape(nextShape, currentShape.X, currentShape.Y)) {
            field.WithShape(currentShape);
            field.WithShape(nextShape);
            currentShape = nextShape;
        }
    }
}
