#pragma once

#include <iterator>
#include <memory>
#include <string>

#include "iterator_exception.hpp"
#include "matrix.hpp"
#include "matrix_exceptions.hpp"

template <typename T>
class constIterator : public std::iterator<std::input_iterator_tag, T> {
public:
    constIterator(const Matrix<T>& matrix, const size_t index = 0)
        : __data(matrix.data), __index(index), __rows(matrix.rows),
          __clms(matrix.columns) {}

    constIterator(const constIterator& iter) = default;

    bool operator!=(constIterator const& i) const {
        return __index != i.__index;
    }
    bool operator==(constIterator const& i) const {
        return __index == i.__index;
    }

    constIterator<T>& operator=(const constIterator<T>& iter) {
        __data = iter.__data;
        __index = iter.__index;
        __rows = iter.__rows;
        __clms = iter.__clms;

        return *this;
    }

    constIterator<T>& operator++() {
        if (__index < __rows * __clms)
            __index++;

        return *this;
    }

    constIterator<T> operator++(int) {
        constIterator<T> iter(*this);

        ++(*this);
        return iter;
    }

    constIterator<T>& operator+(size_t val) const {
        constIterator<T> iter(*this);

        iter.__index += val;

        if (iter.__index > iter.__rows * iter.__clms)
            iter.__index = iter.__rows * iter.__clms;

        return iter;
    }

    constIterator<T>& operator+=(size_t val) {
        __index += val;

        if (__index > __rows * __clms)
            __index = __rows * __clms;

        return (*this);
    }

    const T operator*() const {
        time_t curr_time = time(nullptr);

        if (__data.expired()) {
            throw nullPointerIteratorExc(__FILE__, typeid(*this).name(), __LINE__,
                                         curr_time, "Data pointer is null.");
        }

        if (__index >= __rows * __clms) {
            throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                                 curr_time, "Const iterator out of bounds.");
        }

        std::shared_ptr<T> sh_ptr = __data.lock();

        return sh_ptr.get()[__index];
    }

    const T operator->() const {
        time_t curr_time = time(nullptr);

        if (__data.expired()) {
            throw nullPointerIteratorExc(__FILE__, typeid(*this).name(), __LINE__,
                                         curr_time, "Data pointer is null.");
        }

        if (__index >= __rows * __clms) {
            throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                                 curr_time, "Const iterator out of bounds.");
        }

        std::shared_ptr<T> sh_ptr = __data.lock();

        return sh_ptr.get() + __index;
    }

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
