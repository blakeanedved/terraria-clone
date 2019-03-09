#ifndef _TC_NOISEGENERATOR_HPP_
#define _TC_NOISEGENERATOR_HPP_
#include "pch.hpp"

class NoiseGenerator {
  private:
    noise::module::Perlin pnoise;
    double scale = 300.0;

  public:
    NoiseGenerator(double scale);
    NoiseGenerator(int seed, int octaves, double scale, double persistence,
                   double lacunarity, double frequency);
    ~NoiseGenerator();

    auto GetSeed() -> int;
    auto GetOctaveCount() -> int;
    auto GetScale() -> double;
    auto GetPersistence() -> double;
    auto GetLacunarity() -> double;
    auto GetFrequency() -> double;

    auto SetSeed(int seed) -> void;
    auto SetOctaveCount(int octaves) -> void;
    auto SetScale(double scale) -> void;
    auto SetPersistence(double persistence) -> void;
    auto SetLacunarity(double lacunarity) -> void;
    auto SetFrequency(double frequency) -> void;

    auto Get(double x, double y, double z, int high) -> int;
    auto Get(double x, double y, double z, int low, int high) -> int;
    auto Get(double x, double y, double z, double high) -> double;
    auto Get(double x, double y, double z, double low, double high) -> double;
};

#endif