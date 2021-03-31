#include <cstdio>
#include "model.hpp"
#include "model_io.hpp"
#include "edges_io.hpp"
#include "error.hpp"
#include "edges_io.hpp"
#include "dot_io.hpp"
#include "logger.h"

int read_center(dot_t &d, FILE *file) {
    if (fscanf(file, "%lf %lf %lf", &d.x, &d.y, &d.z) != 3)
        return BAD_CENTER;

    return OK;
}

int read_model(model_t &model, FILE *file) {
    dots_arr_t  dots  = init_dots_array();
    edges_arr_t edges = init_edges_arr();

    int res = get_dots(dots, file);

    if (!res)
        res = get_edges(edges, file);

    if (res) {
        destroy_dots(dots);
    }

    dot_t center;

    if (!res) {
        res = read_center(center, file);
    }

    if (!res) {
        model = init_model(&dots, &edges);
        set_center(model, center);
    } else {
        destroy_dots(dots);
        destroy_edges(edges);
    }


    return res;
}

int read_from_file(model_t &model, const char *filename) {
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        return READ_ERROR;
    }

    model_t temp_model = init_model();
    int res = read_model(temp_model, f);

    if (res) {
        fclose(f);
        return res;
    }

    dots_arr_t dots = get_dots_arr(model);

    if (!dot_arr_is_empty(dots)) {
        destroy_model(model);
    }

    model = temp_model;

    fclose(f);

    return res;
}


static int dump_dots(const model_t &model, FILE *file) {
    dots_arr_t dot_arr = get_dots_arr((model_t &) model);
    unsigned int ndots = get_dots_num(dot_arr);

    if (ndots) {
        fprintf(file, "%u\n", ndots);
        for (unsigned int i = 0; i < ndots; i++) {
            dot_t dot = get_dot(dot_arr, i);
            fprintf(file, "%lf %lf %lf\n", dot.x, dot.y, dot.z);
        }
    }

    fprintf(file, "\n");

    return OK;
}

static int dump_edges(const model_t &model, FILE *file) {
    edges_arr_t edge_arr = get_edges_arr((model_t &) model);
    unsigned int nedges = get_edges_num(edge_arr);

    if (nedges) {
        fprintf(file, "%u\n", nedges);

        for (unsigned int i = 0; i < nedges; i++) {
            edge_t edge = get_edge(edge_arr, i);
            fprintf(file, "%d %d\n", edge.d1, edge.d2);
        }
    }

    fprintf(file, "\n");

    return OK;
}

static int dump_center(const model_t &model, FILE *file) {
    dot_t center = model.center;

    fprintf(file, "%lf %lf %lf\n", center.x, center.y, center.z);

    return OK;
}

int save_to_file(const model_t &model, const char *filename) {
    FILE *f = fopen(filename, "w");

    if (f == NULL) {
        return WRITE_ERROR;
    }

    dump_dots(model, f);
    dump_edges(model, f);
    dump_center(model, f);

    fclose(f);

    return OK;
}
