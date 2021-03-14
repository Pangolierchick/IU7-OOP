#pragma once

#include "model.hpp"
#include "dots_transform.hpp"

enum {
    MOVE_ERROR = 1,
    ROTATE_ERROR,
    SCALE_ERROR
};

int move_model(model_t &model, move_t &move);
int rotate_model(model_t &model, rotate_t &rotate);
int scale_model(model_t &model, scale_t &scale);
