#pragma once

#include "edge.hpp"

struct edges_arr {
    edge_t *edges;
    unsigned int edges_num;
};

using edges_arr_t = struct edges_arr;

edges_arr_t init_edges_arr(edge_t *edges=nullptr, unsigned int en=0);
int allocate_edges(edges_arr_t &edges, unsigned int en);
void destroy_edges(edges_arr_t &edges);
