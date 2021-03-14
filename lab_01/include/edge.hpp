#pragma once

#include "dot.hpp"

struct edge {
    dot_t d1;
    dot_t d2;
};

using edge_t = struct edge;

edge_t init_edge(const dot_t& d1, const dot_t& d2);
