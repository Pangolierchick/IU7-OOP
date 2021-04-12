#pragma once

#include "matrix.hpp"


template <typename T>
Matrix<T>::Matrix() {
    rows = 0;
    columns = 0;
    elem_num = 0;

    data = nullptr;
}

template <typename T>
Matrix<T>::Matrix(Matrix <T>&& m) {
    this->rows = m.Rows();
    this->columns = m.Columns();
    this->elem_num = m.Size();

    try {
        this->data = std::shared_ptr<T>(new T[this->elem_num]);
    } catch (std::bad_alloc) {
        throw NullPtrException(__FILE__, typeid(*this).name(), __LINE__ - 4, time(nullptr), "Allocation failed");
    }

    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] = src_ptr[i * rows + j];
}

template <typename T>
Matrix<T>::Matrix(size_t n, size_t m) {
    this->rows = n;
    this->columns = m;
    this->elem_num = n * m;

    try {
        this->data = std::shared_ptr<T>(new T[this->elem_num]);
    } catch (std::bad_alloc) {
        throw NullPtrException(__FILE__, typeid(*this).name(), __LINE__ - 4, time(nullptr), "Allocation failed");
    }

    std::memset(data.get(), 0, elem_num * sizeof(T));
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) {
    this->rows = list.size();
    this->columns = list.begin().size();
    this->elem_num = rows * columns;

    try {
        this->data = std::shared_ptr<T>(new T[this->elem_num]);
    } catch (std::bad_alloc) {
        throw NullPtrException(__FILE__, typeid(*this).name(), __LINE__ - 4, time(nullptr), "Allocation failed");
    }

    auto buff_ptr = data.get();
    auto list_i = list.begin();

    for (size_t i = 0; list_i < list.end(); i++, list_i++) {

        if (columns != list_i.size()) {
            throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr), "All rows must have equal number of columns");
        }

        auto list_j = list_i.begin();

        for (size_t j = 0; j < list.end(); j++, list_j++)
            buff_ptr[i * rows + j] = *list_j;
    }
}

Matrix<T>::~Matrix() {
    this->data.reset();
}

Matrix<T>& operator =(const Matrix<T>& mtr);
Matrix<T>& operator =(Matrix<T>&& mtr);
Matrix<T>& operator =(std::initializer_list<std::initializer_list<T>> list);
