#include <cstdio>
#include "dot_io.hpp"
#include "dots_arr.hpp"
#include "defines.hpp"

static int read_dots_num(FILE *file) {
    int ndots;
    int rc = fscanf(file, "%d", &ndots);

    return rc == 1 ? ndots : -1;
}

static int read_points(dots_arr_t &dots, FILE *file) {
    unsigned int dot_num = 0;
    int read_res = 3;

    while (read_res == 3 && dot_num < dots.n_dots) {
        read_res = fscanf(file, "%lf %lf %lf", &dots.dots[dot_num].x, &dots.dots[dot_num].y, &dots.dots[dot_num].z);
        dot_num++;
    }
    
    return read_res != 3;
}

int get_dots(dots_arr_t &dots, FILE *file) {
    auto tmp_dots_arr = init_dots_array();
    
    auto dots_num = read_dots_num(file);

    if (dots_num == -1)
        return BAD_DOTS_NUM;
    
    
    if (allocate_dots(tmp_dots_arr, dots_num)) {
        return ALLOC_ERROR;
    }
    
    int rc = read_points(tmp_dots_arr, file);

    if (rc)
        destroy_dots(tmp_dots_arr);
    else {
        dots.dots = tmp_dots_arr.dots;
        dots.n_dots = tmp_dots_arr.n_dots;
    }

    return rc;
}
