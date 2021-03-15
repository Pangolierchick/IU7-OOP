#include <cstdio>

#include "model.hpp"
#include "dot_io.hpp"
#include "edges_io.hpp"
#include "defines.hpp"

model_t init_model(dots_arr_t *da, edges_arr_t *ea) {
    model_t model;

    dots_arr_t dots = { nullptr, 0 };
    
    if (da) {
        dots.dots   = da->dots;
        dots.n_dots = da->n_dots;
    }

    edges_arr_t edges = { nullptr, 0 };
    
    if (ea) {
        edges.edges     = ea->edges;
        edges.edges_num = ea->edges_num;
    }

    model.dots  = dots;
    model.edges = edges;

    return model;
}

void destroy_model(const model_t &model) {
    destroy_dots(model.dots);
    destroy_edges(model.edges);
}
