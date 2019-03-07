#include "pch.hpp"
#include "globals.hpp"
#include "worm.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "tile.hpp"
#include "texture.hpp"

noise::module::Perlin pnoise;
std::unique_ptr<Window> window;
std::vector<std::unique_ptr<Tile>> tiles;