#include "pch.hpp"
#include "globals.hpp"
#include "worm.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "tile.hpp"

noise::module::Perlin pnoise;
std::unique_ptr<Window> window;
std::vector<Tile> tiles;