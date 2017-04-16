#define _CRT_RAND_S
#include <stdlib.h>  // rand_s
#include <iostream>
using namespace std;
#include "Matrix.h"


/* Constructor
* If randomRange > 0, fills the matrix with random numbers from range [0, randomRange] */
Matrix::Matrix(size_t h, size_t w, unsigned int randomRange) {
	this->H = h;
	this->W = w;
	this->N = H * W;
	// cout << "Constructor called with H = " << H << " and W = " << W << "\n";

	// allocate memory:
	data = new int*[H + 1];
	data[0] = new int[W * H];
	for (size_t i = 1; i < H; ++i) {
		data[i] = data[i - 1] + W;
	}
	data[H] = nullptr;

	// generate random numbers
	if (randomRange > 0) {
		unsigned int random;
		for (size_t i = 0; i < N; ++i) {
			rand_s(&random);
			data[0][i] = random % (randomRange + 1);
		}
	};
}

// Copy constructor:
Matrix::Matrix(const Matrix &obj) {
	// cout << "Copy constructor called with H = " << H << " and W = " << W << "\n";
	this->W = obj.W;
	this->H = obj.H;
	this->N = obj.N;

	// allocate memory:
	data = new int*[H + 1];
	data[0] = new int[W * H];
	for (size_t i = 1; i < H; ++i) {
		data[i] = data[i - 1] + W;
	}
	data[H] = nullptr;

	// deep copy:
	for (size_t i = 0; i < N; ++i) {
		this->data[0][i] = obj.data[0][i];
	}
}


// Move constructor:
Matrix::Matrix(Matrix &&obj) {
	// cout << "Move constructor called with H = " << H << " and W = " << W << "\n";
		
	// copy pointers
	this->W = obj.W;
	this->H = obj.H;
	this->N = obj.N;
	this->data = obj.data;

	// empty the original object
	obj.W = 0;
	obj.H = 0;
	obj.N = 0;
	obj.data = nullptr;
}

// Destructor:
Matrix::~Matrix() {
	// cout << "Destructor called (H = " << H << " and W = " << W << ")\n";
	if (data) {
		delete[] data[0];
		delete[] data;
	}
	data = nullptr;
}

// Assignment operator =:
Matrix& Matrix::operator = (Matrix& A) {
	this->W = A.W;
	this->H = A.W;
	this->N = A.N;
	// cout << "Assignment operator called with H = " << H << " and W = " << W << "\n";

	// allocate memory:
	data = new int*[H + 1];
	data[0] = new int[W * H];
	for (size_t i = 1; i < H; ++i) {
		data[i] = data[i - 1] + W;
	}
	data[H] = nullptr;

	// deep copy:
	for (size_t i = 0; i < N; ++i) {
		this->data[0][i] = A.data[0][i];
	}

	return *this;  // Matrix* this;
}

Matrix Matrix::operator + (Matrix& A) {
	Matrix R(W, H);
	for (size_t h = 0; h < H; ++h) {
		for (size_t w = 0; w < W; ++w) {
			R.data[h][w] = this->data[h][w] + A.data[h][w];
		}
	}
	return R;
}

Matrix Matrix::operator - (Matrix& A) {
	Matrix R(W, H);
	for (size_t h = 0; h < H; ++h) {
		for (size_t w = 0; w < W; ++w) {
			R.data[h][w] = data[h][w] - A.data[h][w];
		}
	}
	return R;
}

Matrix Matrix::operator * (Matrix& A) {
	Matrix R(H, H);
	for (size_t h = 0; h < H; ++h) {
		for (size_t w = 0; w < W; ++w) {
			R.data[h][w] = 0;
			for (size_t k = 0; k < W; ++k) {
				R.data[h][w] += this->data[h][k] * A.data[k][w];
			}
		}
	}
	return R;
}



// Input operator >>
istream& operator >> (istream& in, Matrix& A) {
	for (size_t h = 0; h < A.H; ++h) {
		for (size_t w = 0; w < A.W; ++w) {
			cin >> A.data[h][w];
		}
	}
	return in;
}

// Output operator <<
ostream& operator << (ostream& out, Matrix& A) {
	for (size_t h = 0; h < A.H; ++h) {
		for (size_t w = 0; w < A.W; ++w) {
			out << A.data[h][w] << " ";
		}
		out << "\n";
	}
	out << "\n";
	return out;
}