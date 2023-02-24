#include "field-renderer.hpp"

FieldRenderer::FieldRenderer(FieldModel &model)
    : fieldModel(model),
      shader({{"../shaders/field.vert", GL_VERTEX_SHADER},
              {"../shaders/field.frag", GL_FRAGMENT_SHADER},
              {"../shaders/field.geom", GL_GEOMETRY_SHADER}}) {

  for (std::size_t i = 0; i < FieldModel::H; ++i) {
    for (std::size_t j = 0; j < FieldModel::W; ++j) {
      size_t offset = (FieldModel::W * i + j) * 3;
      vertices[offset] = j;
      vertices[offset + 1] = i;
      vertices[offset + 2] = 0;
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

  fieldModel.OnChange(std::bind(&FieldRenderer::OnUpdate, this));
};

void FieldRenderer::OnUpdate() {
  for (int y = 0; y < FieldModel::H; ++y) {
    for (size_t x = 0; x < FieldModel::W; ++x) {
      std::size_t offset = (FieldModel::W * y + x) * 3 + 2;
      vertices[offset] = fieldModel.GetData(x, y) / 100.0;
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FieldRenderer::Render(float dt) {
  shader.use();

  glBindVertexArray(vao);
  glDrawArrays(GL_POINTS, 0, FieldModel::W * FieldModel::H);
  glBindVertexArray(0);
}

void FieldRenderer::Reload() { shader.Reload(); }
