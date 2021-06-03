#pragma once

#include "matrix.h"

#include <initializer_list>
#include <iostream> // for endl

template <typename T>
Matrix<T>::Matrix() {
    rows = 0;
    columns = 0;
    elem_num = 0;

    data = nullptr;
}

template <typename T>
Matrix<T>::Matrix(T** m, size_t row, size_t clm) {
    rows = row;
    columns = clm;
    elem_num = row * clm;

    if (m == nullptr)
        throw NullPtrException(__FILE__, typeid(*this).name(), __LINE__,
                               time(nullptr),
                               "Pointer to matrix is null");

    try {
        this->data = std::shared_ptr<T>(new T[this->elem_num]);
    } catch (std::bad_alloc&) {
        throw badAllocException(__FILE__, typeid(*this).name(), __LINE__,
                                time(nullptr),
                                "Bad alloc");
    }

    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++) {

        if (m[i] == nullptr)
            throw NullPtrException(__FILE__, typeid(*this).name(), __LINE__,
                                   time(nullptr),
                                   "Pointer to matrix is null");

        for (size_t j = 0; j < clm; j++) {
            dst_ptr[i * columns + j] = m[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& m) {
    this->columns = m.columns;
    this->rows = m.rows;
    this->elem_num = m.Size();

    this->data = m.data;
}

template <typename T>
Matrix<T>::Matrix(size_t n, size_t m) {
    this->rows = n;
    this->columns = m;
    this->elem_num = n * m;

    try {
        this->data = std::shared_ptr<T>(new T[n * m]);
    } catch (std::bad_alloc) {
        throw badAllocException(__FILE__, typeid(*this).name(), __LINE__,
                                time(nullptr),
                                "Bad alloc");
    }

    std::memset(data.get(), 0, sizeof(T) * n * m);
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list) {
    this->rows = list.size();
    this->columns = list.begin()->size();
    this->elem_num = rows * columns;

    try {
        this->data = std::shared_ptr<T>(new T[this->elem_num]);
    } catch (std::bad_alloc) {
        throw badAllocException(__FILE__, typeid(*this).name(), __LINE__,
                                time(nullptr),
                                "Bad alloc");
    }

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
            buff_ptr[i * columns + j] = *list_j;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m) : baseMatrix() {
    this->rows = m.rows;
    this->columns = m.columns;
    this->elem_num = rows * columns;

    try {
        this->data = std::shared_ptr<T>(new T[this->elem_num]);
    } catch (std::bad_alloc) {
        throw badAllocException(__FILE__, typeid(*this).name(), __LINE__,
                                time(nullptr),
                                "Bad alloc");
    }

    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * columns + j] = src_ptr[i * columns + j];
    }
}

template <typename T>
Matrix<T>::~Matrix() { this->data.reset(); }

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mtr) {
    try {
        this->data = std::shared_ptr<T>(new T[elem_num]);
    } catch (std::bad_alloc) {
        throw badAllocException(__FILE__, typeid(*this).name(), __LINE__,
                                time(nullptr),
                                "Bad alloc");
    }

    rows = mtr.rows;
    columns = mtr.columns;
    elem_num = rows * columns;

    auto src_ptr = mtr.data.get();
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * columns + j] = src_ptr[i * columns + j];

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& mtr) {
    this->columns = mtr.columns;
    this->rows = mtr.rows;
    this->elem_num = mtr.rows * mtr.columns;

    this->data = mtr.data;

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> list) {
    this->rows = list.size();
    this->columns = list.begin().size();
    this->elem_num = rows * columns;

    try {
        this->data = std::shared_ptr<T>(new T[this->elem_num]);
    } catch (std::bad_alloc) {
        throw badAllocException(__FILE__, typeid(*this).name(), __LINE__,
                                time(nullptr),
                                "Bad alloc");
    }

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
            buff_ptr[i * columns + j] = *list_j;
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
Matrix<T>& Matrix<T>::add(const Matrix<T>& mtrx) {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __add(mtrx);

    return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::add(const T& value) {
    __add(value);

    return (*this);
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
Matrix<T>& Matrix<T>::sub(const Matrix<T>& mtrx) {
    if (rows != mtrx.rows || columns != mtrx.columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__,
                             time(nullptr), "Matrices must have equal sizes.");
    }

    __sub(mtrx);

    return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::sub(const T& value) {
    __sub(value);

    return (*this);
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
            dst_ptr[i * columns + j] *= value;

    return m;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& mtrx) {
    Matrix<T> res = *this * mtrx;

    *this = res;

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T& value) {
    Matrix<T> res = *this * value;

    *this = res;

    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T& value) const {
    Matrix m(*this);

    auto dst_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * m.columns + j] /= value;

    return m;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>& m) const {
    auto inv_m = m.inverted();

    return *this * inv_m;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T& value) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * columns + j] /= value;

    return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const Matrix<T>& m) {
    auto inv_m = m.inverted();

    (*this) *= inv_m;

    return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::divide(const T& value) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * columns + j] *= value;

    return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::divide(const Matrix<T>& m) {
    auto inv_m = m.inverted();

    (*this) *= inv_m;

    return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::mult(const T& value) {
    __mul(value);

    return (*this);
}

template <typename T>
Matrix<T>& Matrix<T>::mult(const Matrix<T>& m) {
    (*this) *= m;
    return (*this);
}

template <typename T>
T& Matrix<T>::operator()(size_t i, size_t j) {
    if (i >= rows || j >= columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                             "Index out of bounds");
    }

    return data.get()[i * columns + j];
}

template <typename T>
const T& Matrix<T>::operator()(size_t i, size_t j) const {
    if (i >= rows || j >= columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                             "Index out of bounds");
    }

    return data.get()[i * columns + j];
}

template <typename T>
MatrixRow<T> Matrix<T>::operator[](size_t row) {
    if (row >= rows) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                             "Index out of bounds");
    }

    return MatrixRow<T>((*this), row);
}

template <typename T>
const MatrixRow<T> Matrix<T>::operator[](size_t row) const {
    if (row >= rows) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                             "Index out of bounds");
    }

    return MatrixRow<T>((*this), row);
}

template <typename _T>
std::ostream& operator<<(std::ostream& os, const Matrix<_T>& mtrx) {
    auto ptr = mtrx.data.get();
    for (size_t i = 0; i < mtrx.rows; i++) {
        for (size_t j = 0; j < mtrx.columns; j++)
            os << ptr[i * mtrx.columns + j] << "\t";

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
constIterator<T> Matrix<T>::cbegin() const {
    constIterator<T> iter((*this), 0);

    return iter;
}

template <typename T>
constIterator<T> Matrix<T>::cend() const {
    constIterator<T> iter((*this), rows * columns);

    return iter;
}

template <typename T>
const T& Matrix<T>::at(size_t i, size_t j) const {
    if (i > rows || j > columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                             "Index out of bounds");
    }

    return data.get()[i * columns + j];
}

template <typename T>
T& Matrix<T>::at(size_t i, size_t j) {
    if (i > rows || j > columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                             "Index out of bounds");
    }

    return data.get()[i * columns + j];
}

template <typename T>
void Matrix<T>::set_at(size_t i, size_t j, const T& value) {
    if (i > rows || j > columns) {
        throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                             "Index out of bounds");
    }

    data.get()[i * columns + j] = value;
}

template <typename T>
Matrix<T> Matrix<T>::fill_zero(size_t r, size_t c) {
    Matrix<T> m(r, c);

    auto ptr = m.data.get();
    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            ptr[i * m.columns + j] = 0;

    return m;
}

template <typename T>
Matrix<T> Matrix<T>::identity_matrix(size_t r, size_t c) {
    Matrix<T> m(r, c);

    auto ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++) {
            ptr[i * m.columns + j] = (i == j);
        }

    return m;
}

template <typename T>
void Matrix<T>::swap_rows(size_t i, size_t j) {
    if (i != j) {
        for (size_t clm = 0; clm < columns; clm++) {
            std::swap(at(i, clm), at(j, clm));
        }
    }
}

template <typename T>
size_t Matrix<T>::__rref() {
    size_t perm = 0;

    for (size_t row = 0, lead = 0; row < rows && lead < columns; ++row, ++lead) {
        size_t i = row;
        while (at(i, lead) == 0) {
            if (++i == rows) {
                i = row;
                if (++lead == columns)
                    return 0;
            }
        }

        swap_rows(i, row);

        perm += i != row;

        if (at(row, lead) != 0) {
            T f = at(row, lead);

            for (size_t clm = 0; clm < columns; clm++)
                at(row, clm) /= f;
        }

        for (size_t j = 0; j < rows; j++) {
            if (j != row) {
                T f = at(j, lead);

                for (size_t clm = 0; clm < columns; clm++)
                    at(j, clm) -= f * at(row, clm);
            }
        }
    }

    return perm;
}

template <typename T>
Matrix<T> Matrix<T>::inverted() const {
    if (rows != columns)
        throw MatrixDetException(__FILE__, typeid(*this).name(), __LINE__ - 1, time(nullptr),
                                 "Matrix must be square");

    Matrix<T> tmp(rows, 2 * rows);

    for (size_t row = 0; row < tmp.rows; ++row) {
        for (size_t clm = 0; clm < tmp.rows; ++clm) {
            tmp.at(row, clm) = this->at(row, clm);
        }
        tmp.at(row, row + tmp.rows) = 1;
    }

    tmp.__rref();

    Matrix<T> inv(rows, rows);

    for (size_t row = 0; row < rows; row++) {
        for (size_t clm = 0; clm < rows; clm++)
            inv.at(row, clm) = tmp(row, clm + rows);
    }

    return inv;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> tr_m(rows, columns);

    for (size_t row = 0; row < rows; row++)
        for (size_t clm = 0; clm < columns; clm++)
            tr_m.at(clm, row) = at(row, clm);

    return tr_m;
}

template <typename T>
Matrix<T> Matrix<T>::__get_minor(size_t x, size_t y) {
    size_t len = rows - 1;
    Matrix<T> res(len, len);

    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len; j++) {
            if (i < x && j < y)
                res.at(i, j) = at(i, j);
            else if (i >= x && j < y)
                res.at(i, j) = at(i + 1, j);
            else if (i < x && j >= y)
                res.at(i, j) = at(i, j + 1);
            else
                res.at(i, j) = at(i + 1, j + 1);
        }
    }

    return res;
}

template <typename T>
T Matrix<T>::det() {
    if (rows == 1 && columns == 1)
        return at(0, 0);

    if (rows != columns)
        throw MatrixDetException(__FILE__, typeid(*this).name(), __LINE__ - 1, time(nullptr),
                                 "Matrix must be square");

    int sgn = 1;
    T determ = 0;

    for (size_t i = 0; i < rows; i++) {
        determ += sgn * at(0, i) * __get_minor(0, i).det();
        sgn = -sgn;
    }

    return determ;
}

template <typename T>
void Matrix<T>::__add(const Matrix<T>& m) {
    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * m.columns + j] += src_ptr[i * m.columns + j];
}

template <typename T>
void Matrix<T>::__add(const T& v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * columns + j] += v;
}

template <typename T>
void Matrix<T>::__sub(const Matrix<T>& m) {
    auto dst_ptr = data.get();
    auto src_ptr = m.data.get();

    for (size_t i = 0; i < m.rows; i++)
        for (size_t j = 0; j < m.columns; j++)
            dst_ptr[i * m.columns + j] -= src_ptr[i * m.columns + j];
}

template <typename T>
void Matrix<T>::__sub(const T& v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * columns + j] -= v;
}

template <typename T>
void Matrix<T>::__mul(const T& v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * columns + j] *= v;
}

template <typename T>
void Matrix<T>::__div(const T& v) {
    auto dst_ptr = data.get();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < columns; j++)
            dst_ptr[i * columns + j] /= v;
}
