#include "model_transform.hpp"
#include "dots_arr_transform.hpp"
#include "error.hpp"

static void move_center(dot_t& center, const move_t& move) {
    move_dot(center, move);
}

int move_model(model_t &model, const move_t &move) {
    dot_t& center = get_center(model);
    move_center(center, move);

    return OK;
}


int rotate_model(model_t &model, const rotate_t &rotate) {
    dots_arr_t dot_arr = get_dots_arr(model);

    return rotate_dots(dot_arr, rotate);
}

int scale_model(model_t &model, const scale_t &scale) {
    dots_arr_t dot_arr = get_dots_arr(model);

    if (dot_arr.dots == nullptr)
        return SCALE_ERROR;

    for (unsigned int i = 0; i < get_dots_num(dot_arr); i++) {
        dot_t& dot = get_dot(dot_arr, i);
        scale_dot(dot, scale);
    }

    return OK;
}
