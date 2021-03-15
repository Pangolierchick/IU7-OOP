#include <cstdio>
#include "edges_io.hpp"
#include "edge.hpp"
#include "edges_arr.hpp"
#include "dot_io.hpp"
#include "dots_arr.hpp"
#include "defines.hpp"

static int read_edges_num(FILE *file) {
    int nedges;
    int rc = fscanf(file, "%d", &nedges);

    return rc == 1 ? nedges : -1;
}

static int read_edge(FILE *file, int *ld, int *rd) {
    return fscanf(file, "%d %d", ld, rd);
}

static int read_edges(FILE *file, edges_arr_t &edges_arr) {
    unsigned int i = 0;
    int rc = 2;

    while (i < edges_arr.edges_num && rc == 2) {
        int ld;
        int rd;

        rc = read_edge(file, &ld, &rd);
        edges_arr.edges[i] = init_edge(ld, rd);
        
        i++;
    }

    printf("Rc after read edges %d\n", rc);

    return rc != 2;
}

int get_edges(edges_arr_t &edges_arr, FILE *file) {
    int edge_num = read_edges_num(file);

    if (edge_num < 0) {
        return BAD_EDGES_NUM;
    }

    edges_arr_t edges = init_edges_arr();

    if (allocate_edges(edges, edge_num) == ALLOC_ERROR) {
        return ALLOC_ERROR;
    }

    int rs = read_edges(file, edges);

    if (rs)
        destroy_edges(edges);
    else {
        edges_arr.edges = edges.edges;
        edges_arr.edges_num = edges.edges_num;
    }
    
    return rs;
}

