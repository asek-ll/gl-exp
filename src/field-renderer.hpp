#ifndef __FIELD_RENDERER_H__
#define __FIELD_RENDERER_H__

#include "field-model.hpp"
#include "shader.hpp"

#include <memory>

class FieldRenderer {
  GLuint vbo, vao;
  GLfloat vertices[FieldModel::W * FieldModel::H * 3] = {0.0f};
  ShaderProgram shader;
  std::shared_ptr<FieldModel> field_model_;

  void OnUpdate();

public:
  FieldRenderer(std::shared_ptr<FieldModel> field_model);
  void Render(float dt);
  void Reload();
};

#endif /* end of include guard: __FIELD_RENDERER_H__ */
