#ifndef _TC_GLOBALS_HPP_
#define _TC_GLOBALS_HPP_
#include "pch.hpp"
#include "window.hpp"

extern bool running;

extern std::vector<std::vector<int> > map;
extern module::Perlin pnoise;
extern const int WORM_MIN_LENGTH = 175;
extern const int WORM_MAX_LENGTH = 250;
extern int seed;

extern const double SCALE = 300.0;
extern const int OCTAVES = 8;
extern const double PERSISTENCE = 0.55;
extern const double LACUNARITY = 2.0;
extern const double FREQUENCY = 0.25;

extern unsigned char color[3];

extern std::unique_ptr<Window> window;

#endif