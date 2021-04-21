#pragma once

#include "const_iterator.h"

template <typename T>
constIterator<T>& constIterator<T>::operator=(const constIterator<T>& iter) {
        __data = iter.__data;
        __index = iter.__index;
        __rows = iter.__rows;
        __clms = iter.__clms;

        return *this;
}

template <typename T>
constIterator<T>& constIterator<T>::operator++() {
    if (__index < __rows * __clms)
        __index++;

    return *this;
}

template <typename T>
constIterator<T> constIterator<T>::operator++(int) {
    constIterator<T> iter(*this);

    ++(*this);
    return iter;
}

template <typename T>
constIterator<T>& constIterator<T>::operator+(size_t val) const {
    constIterator<T> iter(*this);

    iter.__index += val;

    if (iter.__index > iter.__rows * iter.__clms)
        iter.__index = iter.__rows * iter.__clms;

    return iter;
}

template <typename T>
constIterator<T>& constIterator<T>::operator+=(size_t val) {
    __index += val;

    if (__index > __rows * __clms)
        __index = __rows * __clms;

    return (*this);
}

template <typename T>
const T constIterator<T>::operator*() const {
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

template <typename T>
const T constIterator<T>::operator->() const {
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
