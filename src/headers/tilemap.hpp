#ifndef _TC_TILEMAP_HPP_
#define _TC_TILEMAP_HPP_
#include "pch.hpp"
#include "texture.hpp"

class TileMap {
  private:
    std::vector<std::vector<int>> tiles;
    std::vector<std::unique_ptr<Texture>> textures;
    int vTiles, hTiles;

  public:
    TileMap(int width, int height);
    ~TileMap();

    auto Render() -> void;
    auto GenerateColumn(int noiseColumn, int tileColumn) -> void;
};

#endif