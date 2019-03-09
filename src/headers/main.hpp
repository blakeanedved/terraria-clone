#include "globals.hpp"
#include "noisegenerator.hpp"
#include "pch.hpp"
#include "player.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "tilemap.hpp"
#include "window.hpp"
#include "worm.hpp"

noise::module::Perlin pnoise;
std::unique_ptr<Window> window;
std::unique_ptr<NoiseGenerator> noisegen;
std::unique_ptr<TileMap> tm;
std::unique_ptr<Player> player;
int seed;

extern const double SCALE = 300.0;
extern const int OCTAVES = 8;
extern const double PERSISTENCE = 0.55;
extern const double LACUNARITY = 2.0;
extern const double FREQUENCY = 0.25;