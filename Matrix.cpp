#define _CRT_RAND_S
#include <stdlib.h>  // rand_s
#include <iostream>
using namespace std;
#include "Matrix.h"


// Constructor
// If randomRange > 0, fills the matrix with random numbers from range [0, randomRange]
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

// Matrix addition
Matrix Matrix::operator + (Matrix& A) {
	Matrix R(H, W);
	for (size_t i = 0; i < N; ++i) {
		R.data[0][i] = this->data[0][i] + A.data[0][i];
	}
	return R;
}

// Matrix substraction
Matrix Matrix::operator - (Matrix& A) {
	Matrix R(H, W);
	for (size_t i = 0; i < N; ++i) {
		R.data[0][i] = this->data[0][i] - A.data[0][i];
	}
	return R;
}

// Matrix multiplication
Matrix Matrix::operator * (Matrix& A) 
{
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

// Returns a single element
int Matrix::operator ()(size_t h, size_t w) {
	return data[h][w];
}

// Scalar multiplication
// Modifies the matrix itself by multiplying it by scalar
void Matrix::multiplyBy(int scalar) {
	for (size_t i = 0; i < N; ++i) {
		data[0][i] = data[0][i] * scalar;
	}
}

// Modifies the matrix itself by raising it into power
void Matrix::raiseTo(int power) {
	if (power == -1) { // calculate an inverse matrix

		return;
	}

	if (power == 0) { // calculate an identity matrix
		for (size_t h = 0; h < H; ++h) {
			for (size_t w = 0; w < W; ++w) {
				if (h == w)
					data[h][w] = 1;
				else
					data[h][w] = 0;
			}
		}
		return;
	}

	if (power > 1) { // raise matrix into power
		for (size_t i = 1; i < power; ++i) {
			*this = *this * *this;
		}
	}

}

// Calculates and returns a trace of the matrix
long long Matrix::trace() {
	long long result = 0;
	for (size_t i = 0; i < H; ++i) {
		result += data[i][i];
	}
	return result;
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