#include "game.hpp"

#include <GLFW/glfw3.h>

void Game::Init() {
  field.Init();
  currentShape.X = 3;
  currentShape.Y = 0;

  field.WithShape(currentShape);
}

void Game::Render(float dt) { field.Render(); }

bool Game::isKeyPressed(int key, float time, float cd = 0.2, float cds = 0.03) {
  if (Keys[key]) {
    if (KeyProcessedAt[key] < KeyPressedSince[key]) {
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
      field.ClearShape(currentShape);
      currentShape.Y++;
      field.WithShape(currentShape);
    } else {
      field.FreezeShape(currentShape);

      currentShape.Random();
      int yStart = -2;
      for (; yStart <= 0; ++yStart) {
        if (field.IsValidShape(currentShape, 3, yStart)) {
          break;
        }
      }

      currentShape.X = 3;
      currentShape.Y = yStart;

      field.WithShape(currentShape);
      if (Keys[GLFW_KEY_DOWN]) {
        KeyPressedSince[GLFW_KEY_DOWN] = time + 100;
      }
    }

    lastMoveTime = time;
  }

  if (isKeyPressed(GLFW_KEY_LEFT, time)) {
    if (field.IsValidShape(currentShape, currentShape.X - 1, currentShape.Y)) {
      field.ClearShape(currentShape);
      currentShape.X--;
      field.WithShape(currentShape);
    }
  } else if (isKeyPressed(GLFW_KEY_RIGHT, time)) {
    if (field.IsValidShape(currentShape, currentShape.X + 1, currentShape.Y)) {
      field.ClearShape(currentShape);
      currentShape.X++;
      field.WithShape(currentShape);
    }
  } else if (isKeyPressed(GLFW_KEY_DOWN, time, 0.1, 0.01)) {
    if (field.IsValidShape(currentShape, currentShape.X, currentShape.Y + 1)) {
      field.ClearShape(currentShape);
      currentShape.Y++;
      field.WithShape(currentShape);
    }
  } else if (isKeyPressed(GLFW_KEY_UP, time, 0.2f, 0.15f)) {
    Shape nextShape = currentShape.Rotate();
    if (field.IsValidShape(nextShape, currentShape.X, currentShape.Y)) {
      field.ClearShape(currentShape);
      field.WithShape(nextShape);
      currentShape = nextShape;
    }
  }
}
