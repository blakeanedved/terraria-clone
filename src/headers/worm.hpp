#include "pch.hpp"

extern const int WORM_MIN_LENGTH;
extern const int WORM_MAX_LENGTH;
extern std::vector<std::vector<int>> map;
extern noise::module::Perlin pnoise;

struct Point {
    int x, y;
};

class Worm {
  private:
    int x, y;
    std::vector<Point> path;
    double px, py, pz;
    int speed;
    int max_length;
    int scale;
    double side_weight;

  public:
    Worm(int, int);
    void SetMaxLength();
    void Slither();
    void Render(int, int);
};

Worm::Worm(int startx, int starty) {
    x = startx;
    y = starty;

    px = 3.0 * x;
    py = 4.0 * y;
    pz = 5.0 * x * y;

    scale = 300;
    side_weight = 0.25;
}

void Worm::SetMaxLength() {
    double value = pnoise.GetValue((double)x / scale, (double)y / scale,
                                   ((double)x * (double)y) / scale);
    if (value < -1)
        value = -1;
    if (value > 1)
        value = 1;
    max_length = ((value + 1) / 2) * (WORM_MAX_LENGTH - WORM_MIN_LENGTH) +
                 WORM_MIN_LENGTH;
}

void Worm::Slither() {

    int dir;
    Point p;

    for (int i = 0; i < max_length; i++) {

        dir = pnoise.GetValue(px / scale, py / scale, pz / scale);

        if (dir < -1)
            dir = -1;
        else if (dir > 1)
            dir = 1;
        dir = (dir / (0.5 / 0.3)) + 1.5; // get dir between 0.9 and 2.1 radians

        if (dir <
            1.4) { // if the direction is less than relatively straight down
            // weight the direction towards 1.1 to straighten the worm out
            dir = std::max(1.1, dir + (1.1 - dir) * side_weight);
        } else if (dir > 1.6) { // if the direction is greater than relatively
                                // straight down
            // weight the direction towards 1.9 to straighten the worm out
            dir = std::min(1.9, dir + (1.9 - dir) * side_weight);
        }

        dir *= M_PI;

        p.x = path[path.size() - 1].x + floor(speed * cos(dir));
        p.y = path[path.size() - 1].y - floor(speed * sin(dir));

        path.push_back(p);
    }
}

void Worm::Render(int win_x, int win_y) {}
