#pragma once

#include <iterator>
#include <memory>
#include <string>

#include "iterator_exception.h"
#include "matrix.h"
#include "matrix_exceptions.h"

template <typename T>
class constIterator : public std::iterator<std::input_iterator_tag, T> {
public:
    constIterator(const Matrix<T>& matrix, const size_t index = 0)
        : __data(matrix.data), __index(index), __rows(matrix.rows),
          __clms(matrix.columns) {}

    constIterator(const constIterator& iter) = default;

    bool operator!=(constIterator const& i) const { return __index != i.__index; }
    bool operator==(constIterator const& i) const { return __index == i.__index; }

    constIterator<T>& operator=(const constIterator<T>& iter);
    constIterator<T>& operator++();
    constIterator<T>  operator++(int);
    constIterator<T>& operator+(size_t val) const;
    constIterator<T>& operator+=(size_t val);

    const T operator*() const;
    const T operator->() const;

    operator bool() const { return __data.expired(); }
    bool is_end() const { return __index >= __rows * __clms; }
    bool is_valid() const { return !__data.expired(); }

    constIterator<T>& next() { this->operator++(); }

private:
    std::weak_ptr<T> __data = nullptr;

    size_t __index = 0;
    size_t __rows = 0;
    size_t __clms = 0;
};
