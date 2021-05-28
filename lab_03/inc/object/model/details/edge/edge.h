#pragma once

#include <cstddef>

class Edge {
public:
    Edge() = default;
    Edge(const std::size_t &first, const std::size_t &second) : index_1(first), index_2(second) {};
    Edge(const Edge &edge) = default;
    ~Edge() = default;

    std::size_t get_first() const;
    std::size_t get_second() const;

    void set_first(const std::size_t &first);
    void set_second(const std::size_t &second);

private:
    std::size_t index_1;
    std::size_t index_2;
};