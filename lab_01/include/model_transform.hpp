#pragma once

#include "dots_transform.hpp"
#include "error.hpp"
#include "model.hpp"

int move_model(model_t& model, const move_t& move);
int rotate_model(model_t& model, const rotate_t& rotate);
int scale_model(model_t& model, const scale_t& scale);
