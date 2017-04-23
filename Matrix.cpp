#define _CRT_RAND_S
#include <stdlib.h>  // rand_s
#include <iostream>
#include "Matrix.h"
using namespace std;


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

void Matrix::setElement(size_t h, size_t w, int value) {
	data[h][w] = value;
}

// Returns matrix multiplied by a scalar
Matrix Matrix::getMultipliedBy(int scalar) {
	Matrix result(H, W);
	for (size_t i = 0; i < N; ++i) {
		result.setElement(0, i, data[0][i] * scalar);
	}
	return result;
}

// Returns matrix raised into power
Matrix Matrix::getRaisedTo(int power) {
	Matrix result(H, W);
	
	if (power == -1) { // calculate an inverse matrix
		int determinant = calculateDeterminant();
		// if (determinant == 0) return;
		
		for (size_t h = 0; h < H; ++h) {
			for (size_t w = 0; w < W; ++w) {
				result.setElement(h, w, this->getMinor(h, w).calculateDeterminant() * (((h + w) % 2 == 0) ? 1 : -1));
			}
		}
		result = result.getTransposed();
		result = result.getMultipliedBy(1 / determinant);

		return result;
	}

	if (power == 0) { // calculate an identity matrix
		for (size_t h = 0; h < H; ++h) {
			for (size_t w = 0; w < W; ++w) {
				if (h == w)
					result.setElement(h, w, 1);
				else
					result.setElement(h, w, 0);
			}
		}
		return result;
	}

	if (power == 1) {
		return *this;
	}

	if (power == 2) {
		return *this * *this;
	}

	if (power >= 3) { // raise matrix into power
		result = this->getRaisedTo(power / 2);
		result = result * result;
		if (power % 2 == 1)
			result = result * *this;
		return result;
	}

}

// Calculates and returns a trace of the matrix
long long Matrix::calculateTrace() {
	long long result = 0;
	for (size_t i = 0; i < H; ++i) {
		result += data[i][i];
	}
	return result;
}

// Calculates and returns a determinant of the matrix
double Matrix::calculateDeterminant() {
	if (H != W)
		return -1;

	if (H == 1)
		return data[0][0];

	if (H == 2)
		return data[0][0] * data[1][1] - data[1][0] * data[0][1];

	if (H >= 3) {
		double determinant = 0;
		for (size_t k = 0; k < H; ++k) {
			determinant += data[0][k] * getMinor(0, k).calculateDeterminant() * ((k % 2 == 0) ? 1 : -1);
		}
		return determinant;
	}
}

// Returns a minor by excluding one row and one column from the original matrix
Matrix Matrix::getMinor(size_t row, size_t col) {
	Matrix result(H - 1, H - 1);
	size_t res_i, res_j;   // to count the number of row and column of the resulting matrix
	res_i = 0;
	for (size_t i = 0; i < H; ++i) {
		if (i == row) continue;
		res_j = 0;
		for (size_t j = 0; j < W; ++j) {
			if (j == col) continue;
			result.setElement(res_i, res_j, data[i][j]);
			++res_j;
		}
		++res_i;
	}
	return result;
}

// Returns a transposed matrix
Matrix Matrix::getTransposed() {
	Matrix transposed(W, H);
	for (size_t h = 0; h < H; ++h) {
		for (size_t w = 0; w < W; ++w) {
			transposed.setElement(w, h, data[h][w]);
		}
	}
	return transposed;
}

bool Matrix::operator == (const Matrix & B) const {
	for (size_t i = 0; i < N; ++i) {
		if (this->data[0][i] != B.data[0][i])
			return false;
	}
	return true;
}

bool Matrix::operator != (const Matrix & B) const {
	return !(*this == B);
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