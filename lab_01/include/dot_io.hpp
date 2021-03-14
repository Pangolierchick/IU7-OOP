#pragma once

#include "dots_arr.hpp"

enum read_dots_err {
    NO_ERROR,
    BAD_DOTS_NUM,
};

int get_dots(dots_arr_t &dots, FILE *file);
