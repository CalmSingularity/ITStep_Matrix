#pragma once
#define _CRT_RAND_S
#include <stdlib.h>  // rand_s
#include <iostream>


class Matrix {
private:
	size_t H, W, N; // H - height (rows), W - width (columns), N - total number of elements (H * W)
	int** data;

public:

	// Constructor
	// If randomRange > 0, fills the matrix with random numbers from range [0, randomRange]
	Matrix(size_t h, size_t w, unsigned int randomRange = 0);

	Matrix(const Matrix &obj);   // Copy constructor 
	Matrix(Matrix &&obj);        // Move constructor
	~Matrix();                   // Destructor
							 
	Matrix& operator = (Matrix& A);   // Assignment operator =
	Matrix operator + (Matrix& A);    // Matrix addition
	Matrix operator - (Matrix& A);    // Matrix substraction
	Matrix operator * (Matrix& A);    // Matrix multiplication
	
	int operator ()(size_t h, size_t w);  // Returns a single element
	void setElement(size_t h, size_t w, int value);  // Assigns the value to the data[h][w]

	Matrix getMultipliedBy(int scalar);   // Returns matrix multiplied by a scalar
	Matrix getRaisedTo(int power);   // Returns matrix raised into power
	long long calculateTrace();    // Calculates and returns a trace of the matrix
	double calculateDeterminant(); // Calculates and returns a determinant of the matrix
	Matrix getMinor(size_t row, size_t col); // Returns a minor by excluding one row and one column from the original matrix
	Matrix getTransposed();  // Returns a transposed matrix

	bool operator != (const Matrix &B) const;
	bool operator == (const Matrix &B) const;

	friend std::ostream& operator << (std::ostream& out, Matrix& A);
	friend std::istream& operator >> (std::istream& in, Matrix& A);

};

std::ostream& operator << (std::ostream& out, Matrix& A);
std::istream& operator >> (std::istream& in, Matrix& A);