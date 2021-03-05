#include "field.h"

void Field::Init() {
    this->shader = new ShaderProgram("../shaders/field.vs", "../shaders/field.fs", "../shaders/field.gs");

    for ( std::size_t i = 0; i < Heigth; ++i )
    {
        for ( std::size_t j = 0; j < Width; ++j )
        {
          vertices[(Width * i + j) * 3] = j;
          vertices[(Width * i + j) * 3 + 1] = i;
          vertices[(Width * i + j) * 3 + 2] = (rand() % 100) / 100.0;
        }
    }

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(2* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Field::Render() {
    shader->use();

    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, Width * Heigth);
    glBindVertexArray(0);
}

void Field::setData(std::size_t x, std::size_t y, int color) {

  data[y * Width + x] = color;

  std::size_t offset = (Width * y + x) * 3 + 2;

  vertices[offset] = color / 100.0;

  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(GLfloat), sizeof(GLfloat), vertices + offset);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
