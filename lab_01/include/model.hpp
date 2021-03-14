#pragma once

#include <cstdio>
#include "edge.hpp"
#include "dots_arr.hpp"
#include "edges_arr.hpp"

struct model {
    dots_arr_t  dots;
    edges_arr_t edges;
};

using model_t = struct model;

model_t init_model(dots_arr_t *da=nullptr, edges_arr_t *ea=nullptr);
void destroy_model(model_t &model);
