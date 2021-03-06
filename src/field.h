#ifndef __FIELD_H__
#define __FIELD_H__

#include <cstddef>
#include <glad/glad.h>
#include "shader.h"
#include "shape.h"

const std::size_t W = 10;
const std::size_t H = 18;

class Field {

  int data[W * H] = {0};
  GLuint vbo, vao;
  GLfloat vertices[W * H * 3] = {0.0f};
  ShaderProgram *shader;

  void setData(std::size_t x, std::size_t y, int color);

public:
  
  const std::size_t Width = W;
  const std::size_t Heigth = H;

  void Init();
  void Render();
  bool IsValidShape(Shape &shape, int x, int y);
  void FreezeShape(Shape &shape, int color);
  void WithShape(Shape &shape, int color);
};

#endif /* __FIELD_H__ */
