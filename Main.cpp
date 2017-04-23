#include "Matrix.h"
using namespace std;

int main(int argc, char** argv) {

	Matrix A(4, 4, 10);
	cout << "Matrix A:\n" << A;
	Matrix B(4, 4, 10);
	cout << "Matrix B:\n" << B;

	cout << "Matrix A + B:\n" << A + B;

	Matrix C = A - B;
	cout << "Matrix A - B:\n" << C;

	cout << "Matrix A * B:\n" << A * B;

	cout << "Trace of matrix A = " << A.calculateTrace() << "\n\n";

	cout << "Matrix B[1][1] = " << B(1, 1) << "\n\n";

	int x = B(1, 1);
	cout << "Matrix A * " << x << ":\n" << A.getMultipliedBy(x);

	Matrix I = A.getRaisedTo(-1);
	cout << "Matrix A ^ -1:\n" << I;
	cout << "Matrix (A ^ 1) * (A ^ -1):\n" << A * I;

	cout << "Matrix A ^ 0:\n" << A.getRaisedTo(0);
	cout << "Matrix A ^ 1:\n" << A.getRaisedTo(1);
	cout << "Matrix A ^ 2:\n" << A.getRaisedTo(2);
	cout << "Matrix A ^ 3:\n" << A.getRaisedTo(3);

	//cout << "Minor (0, 0) of B:\n" << B.getMinor(0, 0);
	//cout << "Minor (0, 2) of B:\n" << B.getMinor(0, 2);
	//cout << "Minor (2, 1) of B:\n" << B.getMinor(2, 1);

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

	Matrix X(2, 2, 10);
	cout << "Matrix X:\n" << X;
	cout << "Determinant of X = " << X.calculateDeterminant() << endl << endl;

	Matrix Y(3, 3, 10);
	cout << "Matrix Y:\n" << Y;
	cout << "Determinant of Y = " << Y.calculateDeterminant() << endl << endl;

	Matrix Z(4, 4, 10);
	cout << "Matrix Z:\n" << Z;
	cout << "Determinant of Z = " << Z.calculateDeterminant() << endl << endl;

	cout << "Transposed Z: " << endl << Z.getTransposed() << endl << endl;

	Matrix D(3, 3, 10);
	cout << "Matrix D:\n" << D;
	cout << "Matrix D ^ -1:\n" << D.getRaisedTo(-1);

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
