#pragma once

#include "dot.hpp"

struct edge {
    int d1;
    int d2;
};

using edge_t = struct edge;

edge_t init_edge(const int d1, const int d2);
