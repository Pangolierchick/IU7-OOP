#pragma once

#include "edge.hpp"
#include "edges_arr.hpp"

struct model {
    edges_arr_t edges;
};

using model_t = struct model;

model_t init_model(edges_arr_t &edges);
void destroy_model(model_t &model);
