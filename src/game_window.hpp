#ifndef __GAME_WINDOW_H__
#define __GAME_WINDOW_H__

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "game.hpp"

class GameWindow {
  Game &game;
  GLFWwindow *window;

  void keyCallback(int key, int scancode, int action, int mods);

public:
  GameWindow(Game &game);
  virtual ~GameWindow();
  void Run();
};

#endif /* end of include guard: __GAME_WINDOW_H__ */
