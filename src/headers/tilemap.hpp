#ifndef _TC_TILEMAP_HPP_
#define _TC_TILEMAP_HPP_
#include "pch.hpp"
#include "shader.hpp"
#include "texture.hpp"

class TileMap {
  private:
    std::vector<std::vector<int>> tiles;
    std::vector<std::unique_ptr<Texture>> textures;
    int vTiles, hTiles;
    float noiseX, noiseY;
    std::unique_ptr<Shader> shader;
    glm::vec2 offset = glm::vec2(0.0f, 0.0f);
    // float TILE_SIZE = 25.0f;
    float TILE_SIZE = 50.0f;

  public:
    TileMap(int width, int height);
    ~TileMap();

    auto Render() -> void;
    auto GenerateColumn(float noiseColumn, int tileColumn) -> void;
    auto GetTileSize() -> float;
    auto IncrementColumn() -> void;
    auto DecrementColumn() -> void;
    auto IncrementRow() -> void;
    auto DecrementRow() -> void;
    auto GetWorldTile(int tileColumn, int tileRow) -> int;
};

#endif