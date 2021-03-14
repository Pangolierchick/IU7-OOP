#include <cstdio>
#include "model.hpp"

model_t init_model(edges_arr_t &edges) {
    model_t model;

    model.edges = edges;

    return model;
}

void destroy_model(model_t &model) {
    destroy_edges(model.edges);
}
