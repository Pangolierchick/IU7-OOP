#include <cstdio>
#include "edges_arr.hpp"
#include "defines.hpp"

edges_arr_t init_edges_arr(edge_t *edges, unsigned int en) {
    edges_arr_t edge_arr;

    edge_arr.edges     = edges;
    edge_arr.edges_num = en;

    return edge_arr;
}

int allocate_edges(edges_arr_t &edges, unsigned int en) {
    edges.edges = new edge_t[en];

    if (edges.edges != nullptr) {
        edges.edges_num = en;
        return OK;
    }

    return ALLOC_ERROR;
}

void destroy_edges(const edges_arr_t &edges) {
    delete edges.edges;
}
