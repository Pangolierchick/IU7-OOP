#include "draw.hpp"
#include "error.hpp"
#include "model.hpp"
#include "qt_wrap.hpp"

int draw_model(model_t &model, graphic_view_t &field)
{
    dots_arr_t dots = get_dots_arr(model);
    edges_arr_t edges = get_edges_arr(model);

    if (dots.dots == nullptr || edges.edges == nullptr)
    {
        return DRAW_ERROR;
    }

    clean_screen(field);

    for (unsigned int i = 0; i < get_edges_num(edges); i++)
    {
        edge_t edge = get_edge(edges, i);

        dot_t d1 = get_dot(dots, edge.d1);
        dot_t d2 = get_dot(dots, edge.d2);

        dot_t center = get_center(model);

        draw_line(field, {d1.x + center.x, d1.y + center.y, 0}, {d2.x + center.x, d2.y + center.y, 0});
    }

    return OK;
}
