#pragma once

#include "commands.hpp"
#include "draw.hpp"
#include "model_transform.hpp"

struct event {
    commands_t cmd;
};

struct event_data {
    graphic_view_t field;

    move_t move;
    scale_t scale;
    rotate_t rotate;
    char *output_filename;
    char *input_filename;
};

using event_t = struct event;
using event_data_t = struct event_data;

int task_manager(const event_t &event, event_data_t &data);
