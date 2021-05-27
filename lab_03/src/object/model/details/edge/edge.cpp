#include <object/model/details/edge/edge.h>

std::size_t Edge::get_first() const {
    return index_1;
}

std::size_t Edge::get_second() const {
    return index_2;
}

void Edge::set_first(const size_t& first) {
    index_1 = first;
}

void Edge::set_second(const size_t& second) {
    index_2 = second;
}
