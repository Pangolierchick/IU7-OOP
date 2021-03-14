#pragma once

#include "dot.hpp"

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
