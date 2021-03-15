#include "model_transform.hpp"
#include "defines.hpp"

int move_model(const model_t &model, const move_t &move) {
    auto dot_arr = model.dots;

    if (dot_arr.dots == nullptr)
        return MOVE_ERROR;

    for (unsigned int i = 0; i < dot_arr.n_dots; i++) {
        move_dot(dot_arr.dots[i], move);
    }

    return OK;
}


int rotate_model(const model_t &model, const rotate_t &rotate) {
    auto dot_arr = model.dots;

    if (dot_arr.dots == nullptr)
        return ROTATE_ERROR;

    for (unsigned int i = 0; i < dot_arr.n_dots; i++) {
        rotate_dot(dot_arr.dots[i], rotate);
    }

    return OK;
}


int scale_model(const model_t &model, const scale_t &scale) {
    auto dot_arr = model.dots;

    if (dot_arr.dots == nullptr)
        return SCALE_ERROR;

    for (unsigned int i = 0; i < dot_arr.n_dots; i++) {
        scale_dot(dot_arr.dots[i], scale);
    }

    return OK;
}
