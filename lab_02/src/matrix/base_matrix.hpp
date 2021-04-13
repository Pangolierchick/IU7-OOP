#pragma once

#include <cstddef>

class baseMatrix {
  public:
    explicit baseMatrix() : elem_num(0) {}
    explicit baseMatrix(size_t n) : elem_num(n) {}
    virtual ~baseMatrix() = default;

    bool isEmpty() { return elem_num == 0; }
    size_t Rows() const { return rows; }
    size_t Columns() const { return columns; }
    size_t Size() const { return elem_num; }

  protected:
    size_t rows;
    size_t columns;

    size_t elem_num;
};
