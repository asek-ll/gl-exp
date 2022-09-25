#include <iostream>

#include "game_window.hpp"

void size_callback(GLFWwindow *window, int width, int height) {
  if (width > height) {
    glViewport((width - height) / 2, 0, height, height);
  } else {
    glViewport(0, (height - width) / 2, width, width);
  }
}

void GameWindow::keyCallback(int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (key >= 0 && key < 1024) {
    float time = glfwGetTime();

    if (action == GLFW_PRESS) {
      if (!game.Keys[key]) {
        game.KeyPressedSince[key] = time;
      }
      game.Keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      game.KeyPressedSince[key] = 0;
      game.Keys[key] = false;
    }
  }
}

GameWindow::GameWindow(Game &game_) : game(game_) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    throw "Failed to created GLFW window";
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, size_callback);

  auto keyCallback = [](GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
    auto gw = (GameWindow *)glfwGetWindowUserPointer(window);
    gw->keyCallback(key, scancode, action, mods);
  };
  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, keyCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    throw "Failed to initialize GLAD";
  }
}

void GameWindow::Run() {
  game.Init();

  float timeValue = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    float curTime = glfwGetTime();
    float dt = timeValue - curTime;
    timeValue = curTime;

    game.Update(curTime);

    /* glClearColor(0.0f, 0.0f, 0.0f, 0.5f); */
    glClear(GL_COLOR_BUFFER_BIT);

    game.Render(dt);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

GameWindow::~GameWindow() {
  glfwTerminate();
}
