#include "Matrix.h"

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
