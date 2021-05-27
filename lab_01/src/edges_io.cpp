#include "edges_io.hpp"
#include "dot_io.hpp"
#include "dots_arr.hpp"
#include "edge.hpp"
#include "edges_arr.hpp"
#include "error.hpp"
#include "logger.h"
#include <cstdio>

static int read_edges_num(FILE* file) {
    int nedges;
    int rc = fscanf(file, "%d", &nedges);

    if (rc != 1)
        return -1;

    return nedges;
}

static int read_edge(FILE* file, int* ld, int* rd) {
    return fscanf(file, "%d %d", ld, rd) != 2;
}

static int read_edges(FILE* file, edges_arr_t& edges_arr) {
    int rc = 0;
    unsigned int edges_num = get_edges_num(edges_arr);

    for (unsigned int i = 0; i < edges_num && !rc; i++) {
        int ld;
        int rd;

        rc = read_edge(file, &ld, &rd);
        edges_arr.edges[i] = init_edge(ld, rd);
    }

    return rc;
}

int get_edges(edges_arr_t& edges_arr, FILE* file) {
    int edge_num = read_edges_num(file);

    if (edge_num < 0) {
        return BAD_EDGES_NUM;
    }

    edges_arr_t tmp_edges;

    if (allocate_edges(tmp_edges, edge_num) == ALLOC_ERROR) {
        return ALLOC_ERROR;
    }

    int rs = read_edges(file, tmp_edges);

    if (rs)
        destroy_edges(tmp_edges);
    else {
        edges_arr = tmp_edges;
    }

    return rs;
}
