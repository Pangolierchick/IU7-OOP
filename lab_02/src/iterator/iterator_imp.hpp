#pragma once

#include "iterator.h"

#pragma once

#include <iterator>
#include <memory>
#include <string>

#include "iterator_exception.h"
#include "matrix_exceptions.h"

template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& iter) {
    __data = iter.__data;
    __index = iter.__index;
    __rows = iter.__rows;
    __clms = iter.__clms;

    return *this;
}


template <typename T>
Iterator<T>& Iterator<T>::operator++() {
    if (__index < __rows * __clms)
        __index++;

    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> iter(*this);

    ++(*this);
    return iter;
}

template <typename T>
Iterator<T>& Iterator<T>::operator+(size_t val) const {
    Iterator<T> iter(*this);

    iter.__index += val;

    if (iter.__index > iter.__rows * iter.__clms)
        iter.__index = iter.__rows * iter.__clms;

    return iter;
}

template <typename T>
Iterator<T>& Iterator<T>::operator+=(size_t val) {
    __index += val;

    if (__index > __rows * __clms)
        __index = __rows * __clms;

    return (*this);
}

template <typename T>
const T& Iterator<T>::operator*() const {
    time_t curr_time = time(nullptr);

    if (__data.expired()) {
        throw nullPointerIteratorExc(__FILE__, typeid(*this).name(), __LINE__,
                                        curr_time, "Data pointer is null.");
    }

    if (__index > __rows * __clms) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                                curr_time, "Iterator out of bounds.");
    }

    std::shared_ptr<T> sh_ptr = __data.lock();

    auto ptr = sh_ptr.get();

    return ptr[__index];
}

template <typename T>
T& Iterator<T>::operator*() {
    time_t curr_time = time(nullptr);

    if (__data.expired()) {
        throw nullPointerIteratorExc(__FILE__, typeid(*this).name(), __LINE__,
                                        curr_time, "Data pointer is null.");
    }

    if (__index > __rows * __clms) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                                curr_time, "Iterator out of bounds.");
    }

    std::shared_ptr<T> sh_ptr = __data.lock();

    auto ptr = sh_ptr.get();

    return ptr[__index];
}


template <typename T>
const T* Iterator<T>::operator->() const {
    time_t curr_time = time(nullptr);

    if (__data.expired()) {
        throw nullPointerIteratorExc(__FILE__, typeid(*this).name(), __LINE__,
                                        curr_time, "Data pointer is null.");
    }

    if (__index >= __rows * __clms) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                                curr_time, "Iterator out of bounds.");
    }

    std::shared_ptr<T> sh_ptr = __data.lock();

    return sh_ptr.get() + __index;
}

template <typename T>
T* Iterator<T>::operator->() {
    time_t curr_time = time(nullptr);

    if (__data.expired()) {
        throw nullPointerIteratorExc(__FILE__, typeid(*this).name(), __LINE__,
                                        curr_time, "Data pointer is null.");
    }

    if (__index >= __rows * __clms) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                                curr_time, "Iterator out of bounds.");
    }

    std::shared_ptr<T> sh_ptr = __data.lock();

    return sh_ptr.get() + __index;
}
