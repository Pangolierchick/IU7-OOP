#include "dots_arr.hpp"
#include "defines.hpp"

dots_arr_t init_dots_array(dot_t *dots, const unsigned int dots_num) {
    dots_arr_t dots_arr;

    dots_arr.dots   = dots;
    dots_arr.n_dots = dots_num;

    return dots_arr;
}


int allocate_dots(dots_arr_t &dots_arr, const unsigned int dots_num) {
    dots_arr.dots = new dot_t[dots_num]; 

    if (dots_arr.dots != nullptr) {
        dots_arr.n_dots = dots_num;
        return OK;
    }

    return ALLOC_ERROR;
}

void destroy_dots(dots_arr_t &dots_arr) {
    delete dots_arr.dots;
}

dot_t get_dot(dots_arr_t &dots_arr, int ind) {
    return dots_arr.dots[ind];
}
