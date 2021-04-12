#pragma once

#include "dot.hpp"

#define PI 3.14159265

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

void move_dot(dot_t &dot, const move_t &mv);
void scale_dot(dot_t &dot, const scale_t &scale);
void rotate_dot(dot_t &dot, const rotate_t &rotate);
