#include "field.hpp"

void Field::Init() {
  this->shader = new ShaderProgram({
      {"../shaders/field.vert", GL_VERTEX_SHADER},
      {"../shaders/field.frag", GL_FRAGMENT_SHADER},
      {"../shaders/field.geom", GL_GEOMETRY_SHADER},
  });

  for (std::size_t i = 0; i < Heigth; ++i) {
    for (std::size_t j = 0; j < Width; ++j) {
      vertices[(Width * i + j) * 3] = j;
      vertices[(Width * i + j) * 3 + 1] = i;
      // vertices[(Width * i + j) * 3 + 2] = (rand() % 100) / 100.0;
      vertices[(Width * i + j) * 3 + 2] = 0;
    }
  }

  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (void *)(2 * sizeof(float)));
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
  std::size_t offset = (Width * y + x) * 3 + 2;
  vertices[offset] = color / 100.0;
}

bool Field::IsValidShape(Shape &shape, int shapeX, int shapeY) {

  for (int i = 0; i < 16; ++i) {
    int x = shapeX + i % 4;
    int y = Heigth - (shapeY + i / 4) - 1;

    if (shape.Data[i]) {
      if (x < 0 || y < 0) {
        return false;
      }
      if (x >= (int)Width || y >= (int)Heigth || data[y * Width + x] != 0) {
        return false;
      }
    }
  }
  return true;
}

void Field::FreezeShape(Shape &shape) {

  for (size_t i = 0; i < 16; ++i) {
    int x = shape.X + i % 4;
    int y = Heigth - (shape.Y + i / 4) - 1;

    if (shape.Data[i]) {

      data[y * Width + x] = shape.Color;
      setData(x, y, shape.Color);
    }
  }

  size_t dest = 0;
  for (int i = dest; i < Heigth; ++i) {
    bool isComplete = true;
    for (size_t j = 0; j < Width; ++j) {
      if (!data[i * Width + j]) {
        isComplete = false;
        break;
      }
    }
    if (dest != i) {
      std::copy(&data[i * Width], &data[i * Width + Width],
                &data[dest * Width]);

      for (size_t j = 0; j < Width; ++j) {
        vertices[(dest * Width + j) * 3 + 2] =
            vertices[(i * Width + j) * 3 + 2];
      }
    }
    if (!isComplete) {
      dest++;
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Field::WithShape(Shape &shape) {

  for (int i = 0; i < 16; ++i) {
    int x = shape.X + i % 4;
    int y = Heigth - (shape.Y + i / 4) - 1;

    if (shape.Data[i]) {
      setData(x, y, shape.Color);
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Field::ClearShape(Shape &shape) {

  for (int i = 0; i < 16; ++i) {
    int x = shape.X + i % 4;
    int y = Heigth - (shape.Y + i / 4) - 1;

    if (shape.Data[i]) {
      setData(x, y, 0);
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
