#pragma once

#include "base_matrix.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

#include <initializer_list>
#include <memory>

template <typename T>
class Matrix : public baseMatrix {
    // TODO friend section

    public:

//================ CONSTRUCTORS ================
    Matrix();
    Matrix(size_t n, size_t m);
    explicit Matrix(const Matrix<T>& mtrx);
    Matrix(Matrix <T>&& m);
    Matrix(std::initializer_list<std::initializer_list<T>> list);

//================ DESTRUCTORS ================

    ~Matrix();

//=================== EQUAL ===================

	Matrix<T>& operator =(const Matrix<T>& mtr);
	Matrix<T>& operator =(Matrix<T>&& mtr);
	Matrix<T>& operator =(std::initializer_list<std::initializer_list<T>> list);

//================== ADDITION =================

	Matrix<T> operator +(const Matrix<T>& mtrx1) const;
	Matrix<T> operator +(const T& value) const;
	Matrix<T>& operator +=(const Matrix<T>& mtrx);
	void add(const Matrix<T>& mtrx) const;
	void add(const T& value) const;


//================ SUBSTRACTION ===============
	Matrix<T> operator -(const Matrix<T>& mtrx1) const;
	Matrix<T> operator -(const T& value) const;
	Matrix<T>& operator -=(const Matrix<T>& mtrx);
	void sub(const Matrix<T>& mtrx) const;
	void sub(const T& value) const;

//============== MULTIPLICATION ==============
	Matrix<T> operator *(const Matrix<T>& mtrx1) const;
	Matrix<T> operator *(const T& value) const;
	Matrix<T>& operator *=(const Matrix<T>& mtrx);
	void mult(const T& value) const;

//============== DIVISION ==============

	Matrix<T> operator /(const T& value) const;
	void divide(const T& value) const;

	T& operator ()(size_t i, size_t j);
	const T& operator ()(size_t i, size_t j) const;

    template<typename _T>
	friend std::ostream& operator <<(std::ostream& os, const Matrix<_T>& mtrx);
	
	// Iterators
	Iterator<T> begin();
	Iterator<T> end();

	constIterator<T> begin() const;
	constIterator<T> end() const;

	const T& get_value(size_t i, size_t j) const;
	void set_value(size_t i, size_t j, const T& value);

	void fill_zero();
	void identity_matrix();

	private:

	std::shared_ptr<T> data;	
};
