#include "Matrix.h"

int main(int argc, char** argv) {

	Matrix A(4, 4, 10);
	cout << "Matrix A:\n" << A;
	Matrix B(4, 4, 10);
	cout << "Matrix B:\n" << B;

	cout << "Matrix A + B:\n" << A + B;

	Matrix C = A - B;
	cout << "Matrix A - B:\n" << C;

	cout << "Matrix A * B:\n" << A * B;

	cout << "Trace of matrix A = " << A.trace() << "\n\n";

	cout << "Matrix B[1][1] = " << B(1, 1) << "\n\n";

	int x = B(1, 1);
	A.multiplyBy(x);
	cout << "Matrix A * " << x << ":\n" << A;

	A.raiseTo(0);
	cout << "Matrix A ^ 0:\n" << A;

	B.raiseTo(3);
	cout << "Matrix B ^ 3:\n" << B;

	if (A == A)
		cout << "(A == A) is true\n";
	else 
		cout << "(A == A) is false\n";

	if (A != A)
		cout << "(A != A) is true\n";
	else
		cout << "(A != A) is false\n";

	if (A == B)
		cout << "(A == B) is true\n";
	else
		cout << "(A == B) is false\n";

	if (A != B)
		cout << "(A != B) is true\n";
	else
		cout << "(A != B) is false\n";

	cout << endl;

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
