#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

#include "field.h"
#include "game.h"
#include "shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode);

Game game;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  ShaderProgram shaderProgram("../shaders/shader.vert",
                              "../shaders/shader.frag", nullptr);

  float vertices[] = {
      // positions         // colors
      0.8f,  -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
      -0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
      0.0f,  0.8f,  0.0f, 0.0f, 0.0f, 1.0f  // top
  };

  GLuint VBO, VAO;

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  game.Init();

  float timeValue = glfwGetTime();
  float dx = 0;

  while (!glfwWindowShouldClose(window)) {
    float curTime = glfwGetTime();
    float dt = timeValue - curTime;
    timeValue = curTime;

    game.Update(curTime);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    dx += dt / 1;
    /* shaderProgram.use(); */
    /* shaderProgram.setFloat("dx", sin(dx)); */
    /* glBindVertexArray(VAO); */
    /* glDrawArrays(GL_TRIANGLES, 0, 3); */

    game.Render(dt);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  if (width > height) {
    glViewport((width - height) / 2, 0, height, height);
  } else {
    glViewport(0, (height - width) / 2, width, width);
  }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
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
