#include "dots_transform.hpp"

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

void rotate_dot(dot_t &dot, const double angle) {
    
}
