#pragma once

#include "matrix.hpp"

#include <iostream> // for endl

template <typename T>
Matrix<T>::Matrix() {
    rows = 0;
    columns = 0;
    elem_num = 0;

    data = nullptr;
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& m) {
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

template <typename T>
Matrix<T>::Matrix(size_t n, size_t m) {
    this->rows = n;
    this->columns = m;
    this->elem_num = n * m;

    this->data = std::shared_ptr<T>(new T[this->elem_num]);

    std::memset(data.get(), 0, elem_num * sizeof(T));
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) {
    this->rows = list.size();
    this->columns = list.begin()->size();
    this->elem_num = rows * columns;

    this->data = std::shared_ptr<T>(new T[this->elem_num]);

    auto buff_ptr = data.get();
    auto list_i = list.begin();

    for (size_t i = 0; list_i < list.end(); i++, list_i++) {

        if (columns != list_i->size()) {
            throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                                 time(nullptr),
                                 "All rows must have equal number of columns");
        }

        auto list_j = list_i->begin();

        for (size_t j = 0; list_j < list_i->end(); j++, list_j++)
            buff_ptr[i * rows + j] = *list_j;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m) : baseMatrix() {
    this->rows = m.rows;
    this->columns = m.columns;
    this->elem_num = rows * columns;

    this->data = std::shared_ptr<T>(new T[this->elem_num]);

    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] = src_ptr[i * rows + j];
    }
}

template <typename T>
Matrix<T>::~Matrix() { this->data.reset(); }

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mtr) {
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

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& mtr) {
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
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> list) {
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
Matrix<T> Matrix<T>::operator+(const Matrix<T>& mtrx) const {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    Matrix m(*this);

    m.__add(mtrx);

    return m;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T& value) const {
    Matrix m(*this);

    m.__add(value);

    return m;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& mtrx) {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __add(mtrx);

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T& value) {
    __add(value);

    return *this;
}

template <typename T>
void Matrix<T>::add(const Matrix<T>& mtrx) const {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __add(mtrx);
}

template <typename T>
void Matrix<T>::add(const T& value) const {
    __add(value);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& mtrx) const {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    Matrix m(*this);

    m.__sub(mtrx);

    return m;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T& value) const {
    Matrix m(*this);

    m.__add(value);

    return m;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& mtrx) {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __sub(mtrx);

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const T& value) {
    __sub(value);

    return *this;
}

template <typename T>
void Matrix<T>::sub(const Matrix<T>& mtrx) const {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __sub(mtrx);
}

template <typename T>
void Matrix<T>::sub(const T& value) const {
    __sub(value);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& mtrx) const {
    if (columns != mtrx.rows) {
        throw indexException(
            __FILE__, typeid(*this).name(), __LINE__, time(nullptr),
            "Rows of first matrix must be equal to columns of secornd");
    }

    Matrix m(rows, mtrx.columns);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < mtrx.columns; j++) {
            T sum = 0;

            for (size_t k = 0; k < columns; k++) {
                sum += this->at(i, k) * mtrx.at(k, j);
            }

            m.at(i, j) = sum;
        }
    }

    return m;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& value) const {
    Matrix m(*this);

    auto dst_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * rows + j] *= value;
    
    return m;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& mtrx) {
    if (rows != mtrx.columns) {
        throw indexException(
            __FILE__, typeid(*this).name(), __LINE__, time(nullptr),
            "Rows of first matrix must be equal to columns of secornd");
    }

    auto src_ptr = mtrx.data.get();
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            T sum = 0;

            for (size_t k = 0; k < rows; k++)
                sum += dst_ptr[i * rows + k] * src_ptr[i * rows + k];

            dst_ptr[i * rows + j] = sum;
        }
    }

    return (*this);
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T& value) const {
    Matrix m(*this);

    auto dst_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * m.rows + j] /= value;
    
    return m;
}

template <typename T>
Matrix<T> Matrix<T>::operator/=(const T& value) const {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] /= value;
    
    return (*this);
}

template <typename T>
void Matrix<T>::divide(const T& value) const {
    Matrix m(*this);

    auto dst_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * m.rows + j] *= value;
    
    return m;
}

template <typename T>
void Matrix<T>::mult(const T& value) const {
    Matrix m(*this);

    auto dst_ptr = m.data.get();

    __mul(value);
    
    return m;
}

template <typename T>
T& Matrix<T>::operator()(size_t i, size_t j) {
    if (i >= rows || j >= columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
            "Index out of bounds");
    }

    return data.get()[i * rows + j];
}

template <typename T>
const T& Matrix<T>::operator()(size_t i, size_t j) const {
    if (i >= rows || j >= columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
            "Index out of bounds");
    }

    return data.get()[i * rows + j];
}

template <typename _T>
std::ostream& operator<<(std::ostream& os, const Matrix<_T>& mtrx) {
    auto ptr = mtrx.data.get();
    for (size_t i = 0; i < mtrx.rows; i++) {
        for (size_t j = 0; j < mtrx.columns; j++)
            os << ptr[i * mtrx.rows + j] << "\t";
        
        os << std::endl;
    }

    return os;
}

template <typename T>
Iterator<T> Matrix<T>::begin() {
    Iterator<T> iter((*this), 0);

    return iter;
}

template <typename T>
Iterator<T> Matrix<T>::end() {
    Iterator<T> iter((*this), rows * columns);

    return iter;
}

template <typename T>
constIterator<T> Matrix<T>::begin() const {
    constIterator<T> iter((*this), 0);

    return iter;
}


template <typename T>
constIterator<T> Matrix<T>::end() const {
    constIterator<T> iter((*this), rows * columns);

    return iter;
}

template <typename T>
const T& Matrix<T>::at(size_t i, size_t j) const {
    if (i > rows || j > columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
            "Index out of bounds");
    }

    return data.get()[i * rows + j];
}

template <typename T>
T& Matrix<T>::at(size_t i, size_t j) {
    if (i > rows || j > columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
            "Index out of bounds");
    }

    return data.get()[i * rows + j];
}

template <typename T>
void Matrix<T>::set_at(size_t i, size_t j, const T& value) {
    if (i > rows || j > columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
            "Index out of bounds");
    }

    data.get()[i * rows + j] = value;
}

template <typename T>
void Matrix<T>::fill_zero() {
    auto ptr = data.get();
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            ptr[i * rows + j] = 0;
}

template <typename T>
void Matrix<T>::identity_matrix() {
    auto ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++) {
            ptr[i * rows + j] = (i == j);
        }
}

template <typename T>
void Matrix<T>::__add(const Matrix<T>& m) {
    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * m.rows + j] += src_ptr[i * m.rows + j];
}

template <typename T>
void Matrix<T>::__add(const T& v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] += v;
}

template <typename T>
void Matrix<T>::__sub(const Matrix<T>& m) {
    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * m.rows + j] -= src_ptr[i * m.rows + j];
}

template <typename T>
void Matrix<T>::__sub(const T& v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] -= v;
}

template <typename T>
void Matrix<T>::__mul(const T& v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] *= v;
}

template <typename T>
void Matrix<T>::__div(const T& v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * rows + j] /= v;
}
