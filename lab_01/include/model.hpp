#pragma once

#include <cstdio>
#include "edge.hpp"
#include "dots_arr.hpp"
#include "edges_arr.hpp"

struct model {
    dots_arr_t  dots;
    edges_arr_t edges;

    dot_t center;
};

using model_t = struct model;

model_t init_model(dots_arr_t *da=nullptr, edges_arr_t *ea=nullptr);
void destroy_model(model_t &model);

dots_arr_t& get_dots_arr(model_t &model);
edges_arr_t& get_edges_arr(model_t &model);
void set_center(model_t &model, dot_t c);
dot_t& get_center(const model_t& model);
