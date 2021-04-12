#pragma once

typedef struct dot {
    double x;
    double y;
    double z;
} dot_t;

dot_t init_dot(const double x, const double y, const double z);
void clean_dot(const dot_t *dot);
