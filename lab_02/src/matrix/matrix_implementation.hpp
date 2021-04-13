#pragma once

#include "matrix.hpp"

template <typename T> Matrix<T>::Matrix() {
    rows = 0;
    columns = 0;
    elem_num = 0;

    data = nullptr;
}

template <typename T> Matrix<T>::Matrix(Matrix<T> &&m) {
    this->rows = m.rows;
    this->columns = m.columns;
    this->elem_num = m.Size();

    this->data = std::shared_ptr<T>(new T[this->elem_num]);

    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] = src_ptr[i * rows + j];
}

template <typename T> Matrix<T>::Matrix(size_t n, size_t m) {
    this->rows = n;
    this->columns = m;
    this->elem_num = n * m;

    this->data = std::shared_ptr<T>(new T[this->elem_num]);

    std::memset(data.get(), 0, elem_num * sizeof(T));
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) {
    this->rows = list.size();
    this->columns = list.begin().size();
    this->elem_num = rows * columns;

    this->data = std::shared_ptr<T>(new T[this->elem_num]);

    auto buff_ptr = data.get();
    auto list_i = list.begin();

    for (size_t i = 0; list_i < list.end(); i++, list_i++) {

        if (columns != list_i.size()) {
            throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                                 time(nullptr),
                                 "All rows must have equal number of columns");
        }

        auto list_j = list_i.begin();

        for (size_t j = 0; j < list.end(); j++, list_j++)
            buff_ptr[i * rows + j] = *list_j;
    }
}

template <typename T> Matrix<T>::~Matrix() { this->data.reset(); }

template <typename T> Matrix<T> &Matrix<T>::operator=(const Matrix<T> &mtr) {
    this->data = std::shared_ptr<T>(new T[elem_num]);

    rows = mtr.rows;
    columns = mtr.columns;
    elem_num = rows * columns;

    auto src_ptr = mtr.data.get();
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] = src_ptr[i * rows + j];

    return *this;
}

template <typename T> Matrix<T> &Matrix<T>::operator=(Matrix<T> &&mtr) {
    this->data = std::shared_ptr<T>(new T[elem_num]);

    auto src_ptr = mtr.data.get();
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] = src_ptr[i * rows + j];

    mtr.data.reset();

    return *this;
}

template <typename T>
Matrix<T> &
Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> list) {
    this->rows = list.size();
    this->columns = list.begin().size();
    this->elem_num = rows * columns;

    this->data = std::shared_ptr<T>(new T[this->elem_num]);

    auto buff_ptr = data.get();
    auto list_i = list.begin();

    for (size_t i = 0; list_i < list.end(); i++, list_i++) {

        if (columns != list_i.size()) {
            throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                                 time(nullptr),
                                 "All rows must have equal number of columns");
        }

        auto list_j = list_i.begin();

        for (size_t j = 0; j < list.end(); j++, list_j++)
            buff_ptr[i * rows + j] = *list_j;
    }

    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mtrx) const {
    if (m.rows != mtrx.rows || m.columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    Matrix m(*this);

    m.__add(mtrx);

    return m;
}

template <typename T> Matrix<T> Matrix<T>::operator+(const T &value) const {
    Matrix m(*this);

    m.__add(value);

    return m;
}

template <typename T> Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &mtrx) {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __add(mtrx);

    return *this;
}

template <typename T> void Matrix<T>::add(const Matrix<T> &mtrx) const {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __add(mtrx);
}

template <typename T> void Matrix<T>::add(const T &value) const {
    __add(value);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &mtrx) const {
    if (m.rows != mtrx.rows || m.columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    Matrix m(*this);

    m.__sub(mtrx);

    return m;
}

template <typename T> Matrix<T> Matrix<T>::operator-(const T &value) const {
    Matrix m(*this);

    m.__add(value);

    return m;
}

template <typename T> Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &mtrx) {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __sub(mtrx);

    return *this;
}

template <typename T> void Matrix<T>::sub(const Matrix<T> &mtrx) const {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __sub(mtrx);
}

template <typename T> void Matrix<T>::sub(const T &value) const {
    __sub(value);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &mtrx) const {
    if (m.rows != mtrx.columns) {
        throw indexException(
            __FILE__, typeid(*this).name(), __LINE__, time(nullptr),
            "Rows of first matrix must be equal to columns of secornd");
    }

    Matrix m(*this);

    auto src_ptr_r = mtrx.data.get();
    auto src_ptr_l = data.get();

    auto dst_ptr = m.data.get();

    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < column; j++) {
            T sum = 0;

            for (size_t k = 0; k < row; k++)
                sum += src_ptr_l[i * row + k] * src_ptr_r[i * row + k];

            dst_ptr[i * row + j] = sum;
        }
    }

    return m;
}

template <typename T> Matrix<T> Matrix<T>::operator*(const T &value) const {}

template <typename T> Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &mtrx) {}

template <typename T> void Matrix<T>::mult(const T &value) const {}

// Matrix<T>& operator =(std::initializer_list<std::initializer_list<T>> list);

template <typename T> void Matrix<T>::__add(const Matrix<T> &m) {
    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * m.rows + j] += src_ptr[i * m.rows + j];
}

template <typename T> void Matrix<T>::__add(const T &v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] += v;
}

template <typename T> void Matrix<T>::__sub(const Matrix<T> &m) {
    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * m.rows + j] -= src_ptr[i * m.rows + j];
}

template <typename T> void Matrix<T>::__sub(const T &v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] -= v;
}

template <typename T> void Matrix<T>::__mul(const T &v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] *= v;
}

template <typename T> void Matrix<T>::__div(const T &v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] /= v;
}
