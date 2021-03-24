#include <cmath>
#include "dots_transform.hpp"

static inline double to_radians(double angle) {
    return angle * (PI / 180.0);
}


static void x_rotate_dot(dot_t &dot, const double angle, const dot_t& center) {
    double radians = to_radians(angle);

    double temp_y = dot.y;

    double cy = center.y;
    double cz = center.z;

    dot.y =  cy + (dot.y - cy)  * cos(radians) + (dot.z - cz) * sin(radians);
    dot.z =  cz - (temp_y + cy) * sin(radians) + (dot.z - cz) * cos(radians);
}

static void y_rotate_dot(dot_t &dot, const double angle, const dot_t& center) {
    double radians = to_radians(angle);

    double temp_x = dot.x;

    double cx = center.x;
    double cz = center.z;


    dot.x =  dot.x  * cos(radians) + dot.z * sin(radians);
    dot.z = -temp_x * sin(radians) + dot.z * cos(radians);
}

static void z_rotate_dot(dot_t &dot, const double angle, const dot_t& center) {
    double radians = to_radians(angle);

    double temp_x = dot.x;

    dot.x =  dot.x  * cos(radians) - dot.y * sin(radians);
    dot.y =  temp_x * sin(radians) + dot.y * cos(radians);
}

void move_dot(dot_t &dot, const move_t &mv) {
    dot.x += mv.x;
    dot.y += mv.y;
    dot.z += mv.z;
}

void scale_dot(dot_t &dot, const scale_t &scale, const dot_t &center) {
    dot.x *= scale.kx;
    dot.y *= scale.ky;
    dot.z *= scale.kz;
}

void rotate_dot(dot_t &dot, const rotate_t &rotate, const dot_t& center) {
    x_rotate_dot(dot, rotate.ax);
    y_rotate_dot(dot, rotate.ay);
    z_rotate_dot(dot, rotate.az);
}
