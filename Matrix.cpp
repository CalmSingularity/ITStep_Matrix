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
	Matrix(size_t h, size_t w, unsigned int randomRange = 0) {
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
	Matrix(const Matrix &obj) {
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
	Matrix(Matrix &&obj) {
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
	~Matrix() {
		// cout << "Destructor called (H = " << H << " and W = " << W << ")\n";
		if (data) {
			delete[] data[0];
			delete[] data;
		}
		data = nullptr;
	}

	// Assignment operator =:
	Matrix& operator = (Matrix& A) {
		this->W = A.W;
		this->H = A.W;
		this->N = A.N;
		// cout << "Assignment operator called with H = " << H << " and W = " << W << "\n";

		// deep copy:
		for (size_t h = 0; h < this->H; ++h) {
			for (size_t w = 0; w < this->W; ++w) {
				this->data[h][w] = A.data[h][w];
			}
		}
		return *this;  // Matrix* this;
	}

	Matrix operator + (Matrix& A) {
		Matrix R(W, H);
		for (size_t h = 0; h < H; ++h) {
			for (size_t w = 0; w < W; ++w) {
				R.data[h][w] = this->data[h][w] + A.data[h][w];
			}
		}
		return R;
	}

	Matrix operator - (Matrix& A) {
		Matrix R(W, H);
		for (size_t h = 0; h < H; ++h) {
			for (size_t w = 0; w < W; ++w) {
				R.data[h][w] = data[h][w] - A.data[h][w];
			}
		}
		return R;
	}

	Matrix operator * (Matrix& A) {
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

	friend ostream& operator << (ostream& out, Matrix& A);
	friend istream& operator >> (istream& in, Matrix& A);
};


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


int main(int argc, char** argv) {

	Matrix A(3, 3, 10);
	cout << "Matrix A:\n" << A;
	Matrix B(3, 3, 10);
	cout << "Matrix B:\n" << B;

	cout << "Matrix A + B:\n" << A + B;
	
	Matrix C = A - B;
	cout << "Matrix A - B:\n" << C;

	cout << "Matrix A * B:\n" << A * B;

	//size_t H, W;

	//std::cout << "Enter the size of matrix A (H, W): ";
	//std::cin >> H >> W;
	//Matrix A(H, W);
	//std::cout << "Enter matrix A (size " << H << " * " << W << "):\n";
	//std::cin >> A;

	//std::cout << "Enter the size of matrix B (H, W): ";
	//std::cin >> H >> W;
	//Matrix B(H, W);
	//std::cout << "Enter matrix B (size " << H << " * " << W << "):\n";
	//std::cin >> B;

	return 0;
}
