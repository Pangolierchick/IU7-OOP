#include <cstdio>
#include "model.hpp"
#include "model_io.hpp"
#include "edges_io.hpp"
#include "error.hpp"
#include "edges_io.hpp"
#include "dot_io.hpp"
#include "logger.h"

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
    auto dots = get_dots_arr(model);

    
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        return READ_ERROR;
    }

    int res = 0;

    if (dots.dots != nullptr) {
        model_t temp_model = init_model();
        res = get_model(temp_model, f);

        DBG_PRINT("RES: %d\n", res);

        if (!res) {
            destroy_model(model);
            model = temp_model;
        }
    }
    else {
        res = get_model(model, f);
    }

    fclose(f);

    return res;
}


static int dump_dots(const model_t &model, FILE *file) {
    dots_arr_t dot_arr = get_dots_arr((model_t &) model);
    auto ndots = get_dots_num(dot_arr);

    if (ndots) {
        fprintf(file, "%u\n", ndots);
        for (unsigned int i = 0; i < ndots; i++) {
            auto dot = get_dot(dot_arr, i);
            fprintf(file, "%lf %lf %lf\n", dot.x, dot.y, dot.z);
        }
    }

    fprintf(file, "\n");

    return OK;
}

static int dump_edges(const model_t &model, FILE *file) {
    edges_arr_t edge_arr = get_edges_arr((model_t &) model);
    auto nedges = get_edges_num(edge_arr);

    if (nedges) {
        fprintf(file, "%u\n", nedges);

        for (unsigned int i = 0; i < nedges; i++) {
            auto edge = get_edge(edge_arr, i);
            fprintf(file, "%d %d\n", edge.d1, edge.d2);
        }
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
