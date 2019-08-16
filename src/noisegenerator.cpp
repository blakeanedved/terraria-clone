#include "headers/noisegenerator.hpp"

NoiseGenerator::NoiseGenerator(double scale) { this->scale = scale; }

NoiseGenerator::NoiseGenerator(int seed, int octaves, double scale,
                               double persistence, double lacunarity,
                               double frequency) {
    this->pnoise.SetSeed(seed);
    this->pnoise.SetOctaveCount(octaves);
    this->pnoise.SetPersistence(persistence);
    this->pnoise.SetLacunarity(lacunarity);
    this->pnoise.SetFrequency(frequency);

    this->scale = scale;
}

NoiseGenerator::~NoiseGenerator() {}

auto NoiseGenerator::GetSeed() -> int { return this->pnoise.GetSeed(); }
auto NoiseGenerator::GetOctaveCount() -> int {
    return this->pnoise.GetOctaveCount();
}
auto NoiseGenerator::GetScale() -> double { return this->scale; }
auto NoiseGenerator::GetPersistence() -> double {
    return this->pnoise.GetPersistence();
}
auto NoiseGenerator::GetLacunarity() -> double {
    return this->pnoise.GetLacunarity();
}
auto NoiseGenerator::GetFrequency() -> double {
    return this->pnoise.GetFrequency();
}

auto NoiseGenerator::SetSeed(int seed) -> void { this->pnoise.SetSeed(seed); }
auto NoiseGenerator::SetOctaveCount(int octaves) -> void {
    this->pnoise.SetOctaveCount(octaves);
}
auto NoiseGenerator::SetScale(double scale) -> void { this->scale = scale; }
auto NoiseGenerator::SetPersistence(double persistence) -> void {
    this->pnoise.SetPersistence(persistence);
}
auto NoiseGenerator::SetLacunarity(double lacunarity) -> void {
    this->pnoise.SetLacunarity(lacunarity);
}
auto NoiseGenerator::SetFrequency(double frequency) -> void {
    this->pnoise.SetFrequency(frequency);
}

auto NoiseGenerator::Get(double x, double y, double z, int high) -> int {
    return static_cast<int>(this->Get(x, y, z, 0.0, static_cast<double>(high)));
}
auto NoiseGenerator::Get(double x, double y, double z, int low, int high)
    -> int {
    return static_cast<int>(this->Get(x, y, z, static_cast<double>(low),
                                      static_cast<double>(high)));
}
auto NoiseGenerator::Get(double x, double y, double z, double high) -> double {
    return this->Get(x, y, z, 0.0, high);
}
auto NoiseGenerator::Get(double x, double y, double z, double low, double high)
    -> double {
    double value = this->pnoise.GetValue(x / this->scale, y / this->scale,
                                         z / this->scale);

    if (value > 1)
        value = 1;
    else if (value < -1)
        value = -1;

    value = (value + 1) / 2;

    value = (value * (high - low)) + low;

    return value;
}
