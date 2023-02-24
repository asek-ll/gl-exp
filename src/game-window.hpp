#ifndef __GAME_WINDOW_H__
#define __GAME_WINDOW_H__

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "game.hpp"

class GameWindow {
  Game &game_;
  GLFWwindow *window_;

public:
  GameWindow(Game &game);
  virtual ~GameWindow();
  void KeyCallback(int key, int scancode, int action, int mods);
  void Run();
  template <typename S, typename R> void Run2(S state, R renderer) {
    float prev_time = glfwGetTime();

    while (!glfwWindowShouldClose(window_)) {
      float curr_time = glfwGetTime();
      float dt = prev_time - curr_time;
      prev_time = curr_time;

      state.Update(dt);

      glClearColor(0.1f, 0.0f, 0.0f, 0.5f);
      glClear(GL_COLOR_BUFFER_BIT);
      renderer.Render(dt);
      glfwSwapBuffers(window_);

      glfwPollEvents();
    }
  }
};

#endif /* end of include guard: __GAME_WINDOW_H__ */
