#include "model_transform.hpp"
#include "error.hpp"

int move_model(model_t &model, const move_t &move) {
    auto dot_arr = get_dots_arr(model);

    if (dot_arr.dots == nullptr)
        return MOVE_ERROR;

    for (unsigned int i = 0; i < get_dots_num(dot_arr); i++) {
        auto& dot = get_dot(dot_arr, i);
        move_dot(dot, move);
    }

    return OK;
}


int rotate_model(model_t &model, const rotate_t &rotate) {
    auto dot_arr = get_dots_arr(model);

    if (dot_arr.dots == nullptr)
        return ROTATE_ERROR;

    for (unsigned int i = 0; i < get_dots_num(dot_arr); i++) {
        auto& dot = get_dot(dot_arr, i);
        rotate_dot(dot, rotate);
    }

    return OK;
}


int scale_model(model_t &model, const scale_t &scale) {
    auto dot_arr = get_dots_arr(model);

    if (dot_arr.dots == nullptr)
        return SCALE_ERROR;

    for (unsigned int i = 0; i < get_dots_num(dot_arr); i++) {
        auto& dot = get_dot(dot_arr, i);
        scale_dot(dot, scale);
    }

    return OK;
}
