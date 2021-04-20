#pragma once

#include "base_matrix.hpp"
#include "const_iterator.hpp"
#include "iterator.hpp"

#include <initializer_list>
#include <memory>

template <typename T>
class Matrix : virtual public baseMatrix {
    friend Iterator<T>;
    friend constIterator<T>;

public:
    //================ CONSTRUCTORS ================
    Matrix();
    Matrix(size_t n, size_t m);
    explicit Matrix(const Matrix<T>& mtrx);
    Matrix(Matrix<T>&& m);
    Matrix(std::initializer_list<std::initializer_list<T>> list);

    //================ DESTRUCTORS ================

    ~Matrix();

    //=================== EQUAL ===================

    Matrix<T>& operator=(const Matrix<T>& mtr);
    Matrix<T>& operator=(Matrix<T>&& mtr);
    Matrix<T>& operator=(std::initializer_list<std::initializer_list<T>> list);

    //================== ADDITION =================

    Matrix<T> operator+(const Matrix<T>& mtrx) const;
    Matrix<T> operator+(const T& value) const;
    Matrix<T>& operator+=(const Matrix<T>& mtrx);
    Matrix<T>& operator+=(const T& value);
    Matrix<T>& add(const Matrix<T>& mtrx);
    Matrix<T>& add(const T& value);

    //================ SUBSTRACTION ===============
    Matrix<T> operator-(const Matrix<T>& mtrx) const;
    Matrix<T> operator-(const T& value) const;
    Matrix<T>& operator-=(const Matrix<T>& mtrx);
    Matrix<T>& operator-=(const T& value);
    Matrix<T>& sub(const Matrix<T>& mtrx);
    Matrix<T>& sub(const T& value);

    //============== MULTIPLICATION ==============
    Matrix<T> operator*(const Matrix<T>& mtrx) const;
    Matrix<T> operator*(const T& value) const;
    Matrix<T>& operator*=(const Matrix<T>& mtrx);
    Matrix<T>& operator*=(const T& value);
    Matrix<T>& mult(const T& value);
    Matrix<T>& mult(const Matrix<T>& m);

    //============== DIVISION ==============

    Matrix<T> operator/(const T& value) const;
    Matrix<T> operator/(const Matrix<T>& m) const;
    Matrix<T>& operator/=(const T& value);
    Matrix<T>& operator/=(const Matrix<T>& m);
    Matrix<T>& divide(const T& value);
    Matrix<T>& divide(const Matrix<T>& m);

    T& operator()(size_t i, size_t j);
    const T& operator()(size_t i, size_t j) const;

    const T& at(size_t i, size_t j) const;
    T& at(size_t i, size_t j);
    void set_at(size_t i, size_t j, const T& value);

    template <typename _T>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<_T>& mtrx);

    // Iterators
    Iterator<T> begin();
    Iterator<T> end();

    constIterator<T> begin() const;
    constIterator<T> end() const;

    constIterator<T> cbegin() const;
    constIterator<T> cend() const;

    static Matrix<T> fill_zero(size_t r, size_t c);
    static Matrix<T> identity_matrix(size_t r, size_t c);

    void swap_rows(size_t i, size_t j);
    Matrix<T> inverted() const;
    T det();
    Matrix<T> transpose() const;

    Matrix<T> triangle() const;

    class MatrixRow {
    public:
        MatrixRow(const Matrix<T>& m, size_t row) : __m(m), __row(row){};
        explicit MatrixRow(const MatrixRow& r);
        MatrixRow(MatrixRow&& m) : __m(m.__m), __row(m.__row){};

        T& operator[](size_t clm) {
            if (clm >= __m.columns)
                throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                                     "Index out of bounds");

            return __m.data.get()[__row * __m.columns + clm];
        }

        const T& operator[](size_t clm) const {
            if (clm >= __m.columns)
                throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                                     "Index out of bounds");

            return __m.data.get()[__row * __m.columns + clm];
        }

    private:
        const Matrix<T>& __m;
        size_t __row;
    };

    MatrixRow operator[](size_t row) {
        if (row >= rows) {
            throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                                 "Index out of bounds");
        }

        return MatrixRow((*this), row);
    }

    const MatrixRow operator[](size_t row) const {
        if (row >= rows) {
            throw indexException(__FILE__, typeid(*this).name(), __LINE__, time(nullptr),
                                 "Index out of bounds");
        }

        return MatrixRow(*this, row);
    }

private:
    std::shared_ptr<T> data = nullptr;

    void __add(const Matrix<T>& m);
    void __add(const T& v);

    void __sub(const Matrix<T>& m);
    void __sub(const T& m);

    void __mul(const T& v);
    void __div(const T& v);

    size_t __rref();

    Matrix<T> __get_minor(size_t row, size_t clm);
};
