#pragma once

#include <QGraphicsScene>
#include "model.hpp"
#include "draw.hpp"

void draw_line(graphic_view_t &field, dot_t d1, dot_t d2);
void clean_screen(graphic_view_t &field);
