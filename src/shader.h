#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <glad/glad.h>

struct Shader {
  GLenum type;
  const char* path;
};

class ShaderProgram {


public:
  GLuint id;

  ShaderProgram(const char* vertexPath, const char * fragmentPath);
  void use() const;
  void setBool(const char* name, bool value) const;  
  void setInt(const char* name, int value) const;   
  void setFloat(const char* name, float value) const;

};


#endif /* __SHADER_H__ */
