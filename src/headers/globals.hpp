#ifndef _TC_GLOBALS_HPP_
#define _TC_GLOBALS_HPP_
#include "pch.hpp"
#include "window.hpp"
#include "noisegenerator.hpp"
#include "tilemap.hpp"
#include "player.hpp"

extern std::vector<std::vector<int>> map;
extern const int WORM_MIN_LENGTH = 175;
extern const int WORM_MAX_LENGTH = 250;
extern int seed;

extern const double SCALE;
extern const int OCTAVES;
extern const double PERSISTENCE;
extern const double LACUNARITY;
extern const double FREQUENCY;

extern std::unique_ptr<Window> window;
extern std::unique_ptr<NoiseGenerator> noisegen;
extern std::unique_ptr<TileMap> tm;
extern std::unique_ptr<Player> player;

#endif