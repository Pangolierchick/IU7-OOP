#pragma once

#include "dot.hpp"

struct dots_arr {
    dot_t *dots;
    unsigned int n_dots;
};

using dots_arr_t = struct dots_arr;

dots_arr_t init_dots_array(dot_t *dots=nullptr, const unsigned int dots_num=0);
int allocate_dots(dots_arr_t &dots_arr, const unsigned int dots_num);
void destroy_dots(const dots_arr_t &dots_arr);
dot_t get_dot(const dots_arr_t &dots_arr, int ind);
