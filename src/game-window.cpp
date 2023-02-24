#include "game-window.hpp"

#include <functional>

void SizeCallback(GLFWwindow *window, int width, int height) {
  if (width > height) {
    glViewport((width - height) / 2, 0, height, height);
  } else {
    glViewport(0, (height - width) / 2, width, width);
  }
}

void GameWindowKeyCallback(GLFWwindow *window, int key, int scancode,
                           int action, int mods) {
  auto gw = (GameWindow *)glfwGetWindowUserPointer(window);
  gw->KeyCallback(key, scancode, action, mods);
}

void GameWindow::KeyCallback(int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window_, true);
  }

  if (key >= 0 && key < 1024) {
    float time = glfwGetTime();

    if (action == GLFW_PRESS) {
      if (!game_.Keys[key]) {
        game_.KeyPressedSince[key] = time;
      }
      game_.Keys[key] = true;
    } else if (action == GLFW_RELEASE) {
      game_.KeyPressedSince[key] = 0;
      game_.Keys[key] = false;
    }
  }
}

GameWindow::GameWindow(Game &game) : game_(game) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
  if (window_ == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    throw "Failed to created GLFW window";
  }
  glfwMakeContextCurrent(window_);
  glfwSetFramebufferSizeCallback(window_, SizeCallback);

  glfwSetWindowUserPointer(window_, this);
  glfwSetKeyCallback(window_, GameWindowKeyCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    throw "Failed to initialize GLAD";
  }
}

void GameWindow::Run() {
  game_.Init();

  float timeValue = glfwGetTime();

  while (!glfwWindowShouldClose(window_)) {
    float curTime = glfwGetTime();
    float dt = timeValue - curTime;
    timeValue = curTime;

    game_.Update(curTime);

    /* glClearColor(0.0f, 0.0f, 0.0f, 0.5f); */
    glClear(GL_COLOR_BUFFER_BIT);

    game_.Render(dt);

    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}

GameWindow::~GameWindow() { glfwTerminate(); }
