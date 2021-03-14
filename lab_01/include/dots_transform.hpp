#pragma once

#include "dot.hpp"

#define PI 3.1415

struct move {
    double x;
    double y;
    double z;
};

using move_t = struct move;

struct scale {
    double kx;
    double ky;
    double kz;
};

using scale_t = struct scale;

struct rotate {
    double ax;
    double ay;
    double az;
};

using rotate_t = struct rotate;
