#ifndef _TC_PLAYER_HPP_
#define _TC_PLAYER_HPP_
#include "pch.hpp"
#include "texture.hpp"

class Player {
  private:
    glm::vec2 pos;
    glm::vec2 vel;
    std::unique_ptr<Texture> texture;
    GLuint vboID, vaoID, iboID;
    GLfloat VBO[16] = {
        100.f, 100.f, 0.f, 0.f, 150.f, 100.f, 1.f, 0.f,
        100.f, 150.f, 0.f, 1.f, 150.f, 150.f, 1.f, 1.f,
    };
    GLuint IBO[6] = {0, 1, 2, 1, 2, 3};

  public:
    Player(glm::vec2 pos);
    ~Player();

    auto Update(double dt) -> void;
    auto Render() -> void;

  private:
    auto UpdatePos() -> void;
};

#endif