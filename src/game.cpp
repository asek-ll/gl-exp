#include "game.h"
#include <GLFW/glfw3.h>


void Game::Init() {
    field.Init();
    currentShape.X = 3;
    currentShape.Y = 0;

    field.WithShape(currentShape, 100);
}

void Game::Render(float dt) {
    field.Render();
}

void Game::Update(float time) {
    if (time - lastMoveTime > 0.2) {

        if (field.IsValidShape(currentShape, currentShape.X, currentShape.Y + 1)) {
            field.WithShape(currentShape, 0);
            currentShape.Y++;
            field.WithShape(currentShape, 100);
        } else {
            field.FreezeShape(currentShape, 50);
            currentShape.X = 3;
            currentShape.Y = 0;

            field.WithShape(currentShape, 100);
        }

        lastMoveTime = time;
    }

    if ( Keys[GLFW_KEY_LEFT] )
    {
        if (field.IsValidShape(currentShape, currentShape.X-1, currentShape.Y)) {
            field.WithShape(currentShape, 0);
            currentShape.X--;
            field.WithShape(currentShape, 100);
        }
    } else if ( Keys[GLFW_KEY_RIGHT] )
    {
        if (field.IsValidShape(currentShape, currentShape.X+1, currentShape.Y)) {
            field.WithShape(currentShape, 0);
            currentShape.X++;
            field.WithShape(currentShape, 100);
        }
    } else if ( Keys[GLFW_KEY_DOWN] )
    {
        if (field.IsValidShape(currentShape, currentShape.X, currentShape.Y+1)) {
            field.WithShape(currentShape, 0);
            currentShape.Y++;
            field.WithShape(currentShape, 100);
        }
    } else if ( Keys[GLFW_KEY_UP] )
    {
        Shape nextShape = currentShape.Rotate();
        if (field.IsValidShape(nextShape, currentShape.X, currentShape.Y)) {
            field.WithShape(currentShape, 0);
            field.WithShape(nextShape, 100);
            currentShape = nextShape;
        }
    }
}
