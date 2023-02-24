#ifndef __FIELD_RENDERER_H__
#define __FIELD_RENDERER_H__

#include "field-model.hpp"
#include "shader.hpp"

class FieldRenderer {
  GLuint vbo, vao;
  GLfloat vertices[FieldModel::W * FieldModel::H * 3] = {0.0f};
  ShaderProgram shader;
  FieldModel fieldModel;

  void OnUpdate();

public:
  FieldRenderer(FieldModel &model);
  void Render(float dt);
  void Reload();
};

#endif /* end of include guard: __FIELD_RENDERER_H__ */
