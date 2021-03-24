#include "model_transform.hpp"
#include "dots_arr_transform.hpp"
#include "error.hpp"

static int move_center(dot_t center, const move_t& move) {
    move_dot(center, move);
}

int move_model(model_t &model, const move_t &move) {
    auto dot_arr = get_dots_arr(model);

    int mv_res = move_dots(dot_arr, move);
    if (!mv_res) {
        dot_t& center = get_center(model);
        move_center(center, move);
    }

    return mv_res;
}


int rotate_model(model_t &model, const rotate_t &rotate) {
    auto dot_arr = get_dots_arr(model);

    return rotate_dots();
}


int scale_model(model_t &model, const scale_t &scale) {
    auto dot_arr = get_dots_arr(model);

    if (dot_arr.dots == nullptr)
        return SCALE_ERROR;

    for (unsigned int i = 0; i < get_dots_num(dot_arr); i++) {
        dot_t& dot = get_dot(dot_arr, i);
        scale_dot(dot, scale);
    }

    return OK;
}
