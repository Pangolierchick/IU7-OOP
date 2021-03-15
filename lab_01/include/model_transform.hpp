#pragma once

#include "model.hpp"
#include "dots_transform.hpp"

enum {
    MOVE_ERROR = 1,
    ROTATE_ERROR,
    SCALE_ERROR
};

int move_model(const model_t &model, const move_t &move);
int rotate_model(const model_t &model, const rotate_t &rotate);
int scale_model(const model_t &model, const scale_t &scale);
