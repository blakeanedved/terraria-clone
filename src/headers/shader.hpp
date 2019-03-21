#ifndef _TC_SHADER_HPP_
#define _TC_SHADER_HPP_
#include "pch.hpp"

class Shader {
  private:
    GLuint programID;
    std::map<std::string, GLuint> uniforms;

  public:
    Shader(const char *fragmentShader, const char *vertexShader);
    ~Shader();

    auto AddUniform(const std::string &uniformName) -> void;
    auto Bind() -> void;
    auto SetUniform(const std::string &uniformName, GLuint value) -> void;
    auto SetUniform(const std::string &uniformName, glm::mat4 value) -> void;
    auto SetUniform(const std::string &uniformName, glm::vec4 value) -> void;

  private:
    auto LoadShaders(const char *fragmentShader, const char *vertexShader)
        -> GLuint;
};

#endif