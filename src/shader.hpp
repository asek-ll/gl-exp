#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <vector>

class ShaderFile {
  const char *path;
  const GLenum type;

public:
  ShaderFile(const char *path_, const GLenum type_) : path(path_), type(type_) {
    std::cout << "Create shader: " << path << std::endl;
  };

  GLuint Compile() const;
};

class ShaderProgram {

  GLuint id;
  const std::vector<ShaderFile> files;

public:
  ShaderProgram(const std::vector<ShaderFile> files_);
  void use() const;
  void setBool(const char *name, bool value) const;
  void setInt(const char *name, int value) const;
  void setFloat(const char *name, float value) const;
  void Reload();
};

#endif /* __SHADER_H__ */
