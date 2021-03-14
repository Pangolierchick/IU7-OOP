#include <cstdio>
#include "edges_io.hpp"
#include "edge.hpp"
#include "edges_arr.hpp"
#include "dot_io.hpp"
#include "dots_arr.hpp"
#include "defines.hpp"

static int read_edges_num(FILE *file) {
    int nedges;
    int rc = fscanf(file, "%u", &nedges);

    return rc == 1 ? nedges : -1;
}

static int read_edge(FILE *file, int *ld, int *rd) {
    return fscanf(file, "%d %d", ld, rd) != 2;
}

int get_edges(edges_arr_t &edges_arr, FILE *file) {
    auto dots_arr = init_dots_array();
    int rc;

    if ((rc = get_dots(dots_arr, file))) {
        destroy_dots(dots_arr);
        return rc;
    }

    auto tmp_edges_arr = init_edges_arr();

    auto nedges = read_edges_num(file);

    if (nedges == -1)
        return BAD_DOTS_NUM;

    if ((rc = allocate_edges(tmp_edges_arr, nedges))) {
        destroy_dots(dots_arr);
        return rc;
    }

    unsigned int i = 0;
    int read_edge_res = 0;

    while (i < tmp_edges_arr.edges_num && read_edge_res == 0) {
        int ld;
        int rd;

        read_edge_res = read_edge(file, &ld, &rd);

        if (read_edge_res == OK) {
            auto edge = init_edge(get_dot(dots_arr, ld), get_dot(dots_arr, rd));

            tmp_edges_arr.edges[i] = edge;
        }

        i++;
    }

    if (read_edge_res == OK) {
        edges_arr.edges = tmp_edges_arr.edges;
        edges_arr.edges_num = tmp_edges_arr.edges_num;
    }

    return read_edge_res;
}

