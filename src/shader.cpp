#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"

void readFileContent(const char* path, std::stringstream& ss) {
    std::ifstream ifs;
    ifs.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    ifs.open(path);

    ss << ifs.rdbuf();

    ifs.close();
}

int success;
char infoLog[512];

GLuint compileShader(const GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint loadAndCompileShader(const char* path, const GLenum type) {
    std::stringstream shaderStream;
    readFileContent(path, shaderStream);
    return compileShader(type, shaderStream.str().c_str());
}

ShaderProgram::ShaderProgram(const char* vertexPath, const char * fragmentPath) {

    auto vertexId = loadAndCompileShader(vertexPath, GL_VERTEX_SHADER);
    auto fragmentId = loadAndCompileShader(fragmentPath, GL_FRAGMENT_SHADER);

    id = glCreateProgram();

    glAttachShader(id, vertexId);
    glAttachShader(id, fragmentId);

    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}


void ShaderProgram::use() const
{
    glUseProgram(this->id);
}

void ShaderProgram::setBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->id, name), (int)value);
}
void ShaderProgram::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(this->id, name), value);
}
void ShaderProgram::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(this->id, name), value);
}
