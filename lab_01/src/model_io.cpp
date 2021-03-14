#include "model_io.hpp"
#include "edges_io.hpp"
#include "defines.hpp"

int get_model(model_t &model, FILE *file) {
    auto edges = init_edges_arr();
    auto rc = 0;

    if ((rc = get_edges(edges, file))) {
        return rc;
    }

    model = init_model(edges);

    return OK;
}
