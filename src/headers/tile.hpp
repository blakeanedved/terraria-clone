#ifndef _TC_TILE_HPP_
#define _TC_TILE_HPP_
#include "pch.hpp"

extern float TileWidth;
extern float TileHeight;

class Tile {
  private:
    GLuint vaoID;
    GLuint iboID;
    GLuint vboID;
    GLfloat verts[16];
    glm::vec2 position;
    int type;

  public:
    Tile(float x, float y, int type);
    ~Tile();

    auto Render() -> void;
};

#endif