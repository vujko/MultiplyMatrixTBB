#include <iostream>
#include <vector>
#include <tchar.h>
#include "Matrix.h"
#include <string>
#include <fstream>
using namespace std;

void pomnoziSerijski(Matrix& A, Matrix& B) {
	int dim = A.red;
	Matrix C(dim);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			for (int k = 0; k < dim; k++)
				C.data[i*dim + j] += A.data[i*dim + k] * B.data[k*dim + j];
		}
	}
	A = C;
}


Matrix ucitajMatricu(string my_file) {
	string line;
	ifstream file(my_file);

	if (file.is_open()) {
		getline(file, line);
		int dim = stoi(line);
		Matrix m(dim);

		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				getline(file, line);
				m.data[i*dim + j] = stoi(line);
			}
		}
		file.close();
		return m;
	}
	else {
		throw invalid_argument("Nevalidna datoteka");
	}
	return NULL;
}

int main() {
	//try i catch za invalid argument
	Matrix A_matrix = ucitajMatricu("inputA.txt");
	Matrix B_matrix = ucitajMatricu("inputB.txt");
	cout << A_matrix << endl << endl;
	cout << B_matrix << endl << endl;
	pomnoziSerijski(A_matrix, B_matrix);
	cout << A_matrix << endl;
	return 0;
}