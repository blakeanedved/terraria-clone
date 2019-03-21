#ifndef _TC_PLAYER_HPP_
#define _TC_PLAYER_HPP_
#include "pch.hpp"
#include "texture.hpp"

class Player {
  private:
    glm::vec2 tilePos;
    glm::vec2 worldPos;
    glm::vec2 vel;
    std::unique_ptr<Texture> texture;
    GLuint vboID, vaoID, iboID;
    GLfloat VBO[16];
    GLuint IBO[6] = {0, 1, 2, 1, 2, 3};
    float movementSpeed = 200.0f;

  public:
    Player(glm::vec2 pos);
    ~Player();

    auto GetWorldX() -> float;
    auto GetWorldY() -> float;
    auto GetTileX() -> int;
    auto GetTileY() -> int;
    auto Update(double dt) -> void;
    auto Render() -> void;

    // private:
    //   auto UpdatePos() -> void;
};

#endif