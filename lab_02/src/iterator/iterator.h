#pragma once

#include <iterator>
#include <memory>
#include <string>

#include "iterator_exception.h"
#include "matrix_exceptions.h"

template <typename T>
class Matrix;

template <typename T>
class Iterator : public std::iterator<std::input_iterator_tag, T> {
public:
    Iterator(const Matrix<T>& matrix, const size_t index = 0)
        : __data(matrix.data), __index(index), __rows(matrix.rows),
          __clms(matrix.columns) {}

    Iterator(const Iterator& iter) = default;

    bool operator!=(Iterator const& i) const { return __index != i.__index; }
    bool operator==(Iterator const& i) const { return __index == i.__index; }

    Iterator<T>& operator=(const Iterator<T>& iter);

    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    Iterator<T>& operator+(size_t val) const;
    Iterator<T>& operator+=(size_t val);

    const T& operator*() const;
    T& operator*();

    const T* operator->() const;
    T* operator->();

    operator bool() const { return __data.expired(); }
    bool is_end() const { return __index >= __rows * __clms; }
    bool is_valid() const { return !__data.expired(); }

    Iterator<T>& next() { this->operator++(); }

private:
    std::weak_ptr<T> __data = nullptr;

    size_t __index = 0;
    size_t __rows = 0;
    size_t __clms = 0;
};
