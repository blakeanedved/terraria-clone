#ifndef _TC_GLOBALS_HPP_
#define _TC_GLOBALS_HPP_
#include "camera.hpp"
#include "noisegenerator.hpp"
#include "pch.hpp"
#include "player.hpp"
#include "tilemap.hpp"
#include "window.hpp"

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
extern std::unique_ptr<Camera> camera;

#endif