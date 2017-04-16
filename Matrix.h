#pragma once
#define _CRT_RAND_S
#include <stdlib.h>  // rand_s
#include <iostream>
using namespace std;


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

	void multiplyBy(int scalar);   // Scalar multiplication
	void raiseTo(int power);       // Raise into power
	long long trace();             // Calculates and returns a trace of the matrix

	bool operator != (const Matrix &B) const;
	bool operator == (const Matrix &B) const;

	friend ostream& operator << (ostream& out, Matrix& A);
	friend istream& operator >> (istream& in, Matrix& A);

};

istream& operator >> (istream& in, Matrix& A);
ostream& operator << (ostream& out, Matrix& A);