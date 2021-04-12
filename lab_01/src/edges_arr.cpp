#include "edges_arr.hpp"
#include "error.hpp"
#include <cstdio>

edges_arr_t init_edges_arr(edge_t *edges, unsigned int en)
{
    edges_arr_t edge_arr;

    edge_arr.edges = edges;
    edge_arr.edges_num = en;

    return edge_arr;
}

int allocate_edges(edges_arr_t &edges, unsigned int en)
{
    edges.edges = new edge_t[en];

    if (edges.edges != nullptr)
    {
        edges.edges_num = en;
        return OK;
    }

    return ALLOC_ERROR;
}

void destroy_edges(edges_arr_t &edges)
{
    delete edges.edges;
    edges.edges = nullptr;
    edges.edges_num = 0;
}

unsigned int get_edges_num(edges_arr_t &edges)
{
    return edges.edges_num;
}

edge_t &get_edge(edges_arr_t &edges, int ind)
{
    return edges.edges[ind];
}
