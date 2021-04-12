#include <cstdio>

#include "dot_io.hpp"
#include "edges_io.hpp"
#include "error.hpp"
#include "model.hpp"

model_t init_model(dots_arr_t *da, edges_arr_t *ea) {
    model_t model;

    dots_arr_t dots = {nullptr, 0};

    if (da) {
        dots.dots = da->dots;
        dots.n_dots = da->n_dots;
    }

    edges_arr_t edges = {nullptr, 0};

    if (ea) {
        edges.edges = ea->edges;
        edges.edges_num = ea->edges_num;
    }

    model.dots = dots;
    model.edges = edges;

    model.center = init_dot(0, 0, 0);

    return model;
}

dots_arr_t &get_dots_arr(model_t &model) { return model.dots; }

edges_arr_t &get_edges_arr(model_t &model) { return model.edges; }

void set_center(model_t &model, dot_t c) { model.center = c; }

dot_t &get_center(model_t &model) { return model.center; }

void destroy_model(model_t &model) {
    destroy_dots(model.dots);
    destroy_edges(model.edges);
}
