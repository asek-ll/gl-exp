#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>
#include <string>

class ShaderProgram {

  GLuint id;

public:
  ShaderProgram(const char *vertexPath, const char *fragmentPath,
                const char *geometryPath);
  void use() const;
  void setBool(const char *name, bool value) const;
  void setInt(const char *name, int value) const;
  void setFloat(const char *name, float value) const;
};

#endif /* __SHADER_H__ */
