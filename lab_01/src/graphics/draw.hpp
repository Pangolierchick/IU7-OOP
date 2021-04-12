#pragma once

#include "model.hpp"
#include <QGraphicsScene>

#define DRAW_ERROR 120

struct graphic_view {
    QGraphicsScene *scene;

    double width;
    double height;

    double start_x;
    double start_y;
};

using graphic_view_t = struct graphic_view;

void draw_line(graphic_view_t &field, dot_t d1, dot_t d2);
int draw_model(model_t &model, graphic_view_t &field);
