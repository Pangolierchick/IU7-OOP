#include "draw.hpp"
#include "model.hpp"
#include "error.hpp"
#include "qt_wrap.hpp"

int draw_model(model_t &model, graphic_view_t &field) {
    dots_arr_t  dots  = get_dots_arr(model);
    edges_arr_t edges = get_edges_arr(model);

    if (dots.dots == nullptr || edges.edges == nullptr) { 
        return DRAW_ERROR;
    }

    clean_screen(field);

    for (unsigned int i = 0; i < get_edges_num(edges); i++) {
        auto edge = get_edge(edges, i);

        dot_t d1 = get_dot(dots, edge.d1);
        dot_t d2 = get_dot(dots, edge.d2);

        printf("Drawing: (%lf %lf) (%lf %lf)\n", d1.x, d1.y, d2.x, d2.y);
        
        draw_line(field, d1, d2);
    }

    return OK;
}
