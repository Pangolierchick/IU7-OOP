#include "draw.hpp"
#include "model.hpp"
#include "defines.hpp"

static inline double move_x_to_center(double x, double width) {
    return x + width / 2.0;
}

static inline double move_y_to_center(double y, double height) {
    return y + height / 2.0;
}

void draw_line(graphic_view_t &field, edge_t &edge, dots_arr_t &dots) {
    dot_t d1 = dots.dots[edge.d1];
    dot_t d2 = dots.dots[edge.d2];

    field.scene->addLine(move_x_to_center(d1.x, field.width), 
                         move_y_to_center(d1.y, field.height),
                         move_x_to_center(d2.x, field.width), 
                         move_y_to_center(d2.y, field.height));
}

int draw_model(model_t &model, graphic_view_t &field) {
    field.scene->clear();
    
    dots_arr_t dots   = model.dots;
    edges_arr_t edges = model.edges;

    if (dots.dots == nullptr || edges.edges == nullptr) { 
        return DRAW_ERROR;
    }

    for (unsigned int i = 0; i < edges.edges_num; i++) {
        draw_line(field, edges.edges[i], dots);
    }

    return OK;
}
