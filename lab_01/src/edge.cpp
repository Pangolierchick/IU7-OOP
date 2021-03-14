#include "edge.hpp"

edge_t init_edge(const dot_t& d1, const dot_t& d2) {
    edge_t edge;

    edge.d1 = d1;
    edge.d2 = d2;

    return edge;
}
