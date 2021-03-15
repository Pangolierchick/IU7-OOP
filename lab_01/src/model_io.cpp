#include <cstdio>
#include "model.hpp"
#include "model_io.hpp"
#include "edges_io.hpp"
#include "defines.hpp"
#include "edges_io.hpp"
#include "dot_io.hpp"

int get_model(model_t &model, FILE *file) {
    auto dots  = init_dots_array();
    auto edges = init_edges_arr();

    int res = get_dots(dots, file);

    if (res)
        return res;

    res = get_edges(edges, file);

    if (res) {
        destroy_dots(dots);
        return res;
    }

    model = init_model(&dots, &edges);

    return OK;
}

int read_from_file(model_t &model, const char *filename) {
    if (model.dots.dots != nullptr) {
        return ALREADY_LOADED;
    }
    
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        return READ_ERROR;
    }

    return get_model(model, f);
}


static int dump_dots(const model_t &model, FILE *file) {
    dots_arr_t dot_arr = model.dots;

    if (dot_arr.dots) {
        fprintf(file, "%u\n", dot_arr.n_dots);
        for (unsigned int i = 0; i < dot_arr.n_dots; i++)
            fprintf(file, "%lf %lf %lf\n", dot_arr.dots[i].x, dot_arr.dots[i].y, dot_arr.dots[i].z);
    }

    fprintf(file, "\n");

    return OK;
}

static int dump_edges(const model_t &model, FILE *file) {
    edges_arr_t edge_arr = model.edges;

    if (edge_arr.edges) {
        fprintf(file, "%u\n", edge_arr.edges_num);

        for (unsigned int i = 0; i < edge_arr.edges_num; i++)
            fprintf(file, "%d %d\n", edge_arr.edges[i].d1, edge_arr.edges[i].d2);
    }

    fprintf(file, "\n");

    return OK;
}

int save_to_file(const model_t &model, const char *filename) {
    FILE *f = fopen(filename, "w");

    if (f == NULL) {
        return WRITE_ERROR;
    }

    dump_dots(model, f);
    dump_edges(model, f);

    fclose(f);

    return OK;
}
