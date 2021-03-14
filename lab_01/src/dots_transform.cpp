#include <cmath>
#include "dots_transform.hpp"

static inline double to_radians(double angle) {
    return angle * (PI / 180);
}


static void x_rotate_dot(dot_t &dot, const double angle) {
    double radians = to_radians(angle);

    double temp_y = dot.y;

    dot.y =  dot.y  * cos(radians) + dot.z * sin(radians);
    dot.z = -temp_y * sin(radians) + dot.z * cos(radians);
}

static void y_rotate_dot(dot_t &dot, const double angle) {
    double radians = to_radians(angle);

    double temp_x = dot.x;

    dot.x =  dot.x  * cos(radians) + dot.z * sin(radians);
    dot.z = -temp_x * sin(radians) + dot.z * cos(radians);
}

static void z_rotate_dot(dot_t &dot, const double angle) {
    double radians = to_radians(angle);

    double temp_x = dot.x;

    dot.x =  dot.x  * cos(radians) + dot.y * sin(radians);
    dot.y = -temp_x * sin(radians) + dot.y * cos(radians);
}



void move_dot(dot_t &dot, const move_t &mv) {
    dot.x += mv.x;
    dot.y += mv.y;
    dot.z += mv.z;
}

void scale_dot(dot_t &dot, const scale_t &scale) {
    dot.x *= scale.kx;
    dot.y *= scale.ky;
    dot.z *= scale.kz;
}

void rotate_dot(dot_t &dot, const rotate_t &rotate) {
    
}
