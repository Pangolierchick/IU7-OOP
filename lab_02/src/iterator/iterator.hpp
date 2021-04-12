#pragma once

#include <iterator>
#include <memory>
#include <string>

#include "matrix.hpp"
#include "matrix_exceptions.hpp"

template <typename T>
class Iterator : public std::iterator<std::input_iterator_tag, T>{
    public:
        Iterator(const Matrix<T>& matrix, const size_t index=0) : __data(matrix.data), __index(index), __rows(matrix.Row()), __clms(matrix.Column()) {}

        Iterator(const Iterator& iter) = default;

        bool operator !=(Iterator const& i) const { return __index != i.__index; }
        bool operator ==(Iterator const& i) const { return __index == i.__index; }

        Iterator<T>& operator =(const Iterator<T>& iter) {
            __data  = iter.__data;
            __index = iter.__index;
            __rows  = iter.__rows;
            __clms  = iter.__clms;

            return this;
        }

    private:
    

};
