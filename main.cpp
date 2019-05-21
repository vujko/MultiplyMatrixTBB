#include <iostream>
#include <vector>
#include <tchar.h>
#include "Matrix.h"
#include <string>
#include <fstream>
#include "ParallelMultiplication.h"

using namespace std;

void pomnoziSerijski(Matrix& A, Matrix& B) {
	int dim = A.red;
	Matrix C(dim);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			for (int k = 0; k < dim; k++)
				C(i, j) += A(i,k) * B(k,j);
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
	try {
		Matrix A_matrix = ucitajMatricu("inputA.txt");
		Matrix B_matrix = ucitajMatricu("inputB.txt");

		cout << "Matrica A:" << endl;
		cout << A_matrix << endl << endl;
		cout << "Matrica B:" << endl;
		cout << B_matrix << endl << endl;
		pomnoziSerijski(A_matrix, B_matrix);
		cout << "Matrica A*B:" << endl;
		cout << A_matrix << endl;

		A_matrix = ucitajMatricu("inputA.txt");
		ParallelMultiplication::multiply(A_matrix, B_matrix);
		cout << endl << "A posle paralelnog mnozenja" << endl;
		cout << A_matrix << endl;



		
		return 0;
	}
	catch (runtime_error e) {
		cout << e.what() << endl;
		return -1;
	}
	
}