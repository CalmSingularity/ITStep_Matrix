#pragma once
#define _CRT_RAND_S
#include <stdlib.h>  // rand_s
#include <iostream>
using namespace std;

template <class T>
class Matrix {
private:
	size_t H, W, N; // H - height (rows), W - width (columns), N - total number of elements (H * W)
	T** data;

public:

	// Constructor
	// If randomRange > 0, fills the matrix with random numbers from range [0, randomRange]
	Matrix(size_t h, size_t w, T randomRange = 0);

	Matrix(const Matrix &obj);   // Copy constructor 
	Matrix(Matrix &&obj);        // Move constructor
	~Matrix();                   // Destructor
							 
	Matrix& operator = (Matrix& A);   // Assignment operator =
	Matrix operator + (Matrix& A);    // Matrix addition
	Matrix operator - (Matrix& A);    // Matrix substraction
	Matrix operator * (Matrix& A);    // Matrix multiplication
	
	T operator ()(size_t h, size_t w);  // Returns a single element
	void setElement(size_t h, size_t w, T value);  // Assigns the value to the data[h][w]

	Matrix getMultipliedBy(T scalar);  // Returns matrix multiplied by a scalar
	Matrix getRaisedTo(T power);   // Returns matrix raised into power
	T calculateTrace();    // Calculates and returns a trace of the matrix
	T calculateDeterminant(); // Calculates and returns a determinant of the matrix
	Matrix getMinor(size_t row, size_t col); // Returns a minor by excluding one row and one column from the original matrix
	Matrix getTransposed();   // Returns a transposed matrix

	bool operator != (const Matrix &B) const;
	bool operator == (const Matrix &B) const;

	friend ostream& operator << (ostream& out, Matrix& A);
	friend istream& operator >> (istream& in, Matrix& A);

};

template <class T>
istream& operator >> (istream& in, Matrix<T>& A);
template <class T>
ostream& operator << (ostream& out, Matrix<T>& A);