#include <cstdio>
#include "dot_io.hpp"
#include "dots_arr.hpp"
#include "error.hpp"
#include "logger.h"

static int read_dots_num(FILE *file) {
    int ndots;
    int rc = fscanf(file, "%d", &ndots);

    if (rc != 1)
        return -1;
    
    return ndots;
}

static int read_point(dot_t &dot, FILE *file) {
    return fscanf(file, "%lf %lf %lf", &dot.x, &dot.y, &dot.z) != 3;
}

static int read_points(dots_arr_t &dots, FILE *file) {
    int read_res = 0;

    unsigned int dots_count = get_dots_num(dots);

    for (unsigned int i = 0; i < dots_count && !read_res; i++) {
        dot_t& dot = get_dot(dots, i);
        read_res = read_point(dot, file);
    }
    
    return read_res;
}

int get_dots(dots_arr_t &dots, FILE *file) {
    auto dots_num = read_dots_num(file);

    if (dots_num == -1)
        return BAD_DOTS_NUM;

    dots_arr_t tmp_dots_arr;

    if (allocate_dots(tmp_dots_arr, dots_num)) {
        return ALLOC_ERROR;
    }
    
    int rc = read_points(tmp_dots_arr, file);

    if (rc)
        destroy_dots(tmp_dots_arr);
    else {
        dots = tmp_dots_arr;
    }

    return rc;
}
