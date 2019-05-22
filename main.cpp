#include <iostream>
#include <vector>
#include "Matrix.h"
#include <string>
#include <fstream>
#include "ParallelMultiplication.h"
#include <tbb/tick_count.h>

using namespace std;

#define M_SIZE 40
//Debug verzija M_SIZE 40:
//otprilike jednako vreme izvrsenje

//Realease verzija M_SIZE 150
//otprilike jednako vreme izvsenje

//Sto veci m_size to paralelno postaje brzi
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
		//Matrix A_matrix = ucitajMatricu("inputA.txt");
		//Matrix B_matrix = ucitajMatricu("inputB.txt");

		//cout << "Matrica A:" << endl;
		//cout << A_matrix << endl << endl;
		//cout << "Matrica B:" << endl;
		//cout << B_matrix << endl << endl;


		//tick_count start = tick_count::now();
		//pomnoziSerijski(A_matrix, B_matrix);
		//tick_count end = tick_count::now();

		//cout << "Matrica A*B:" << endl;
		//cout << A_matrix << endl;
		//cout << "================================================================" << endl;
		//cout <<  "Serijsko racunanje matrice A je trajalo: " << (end - start).seconds() * 1000 << "ms." << endl << endl;

		//A_matrix = ucitajMatricu("inputA.txt");
		//start = tick_count::now();
		//ParallelMultiplication::multiply(A_matrix, B_matrix);
		//end = tick_count::now();
		//cout << endl << "A posle paralelnog mnozenja" << endl;
		//cout << A_matrix << endl;
		//cout << "=================================================================" << endl;
		//cout << "Paralelno racunanje matrice A je trajalo: " << (end - start).seconds() * 1000 << "ms." << endl << endl;


		Matrix Aprim = Matrix::gen_matrix(M_SIZE);
		Matrix B = Matrix::gen_matrix(M_SIZE);

		Matrix A = Aprim;

		cout << "Matrica A:" << endl;
		cout << A << endl << endl;
		cout << "Matrica B:" << endl;
		cout << B << endl << endl;


		tick_count start = tick_count::now();
		pomnoziSerijski(A, B);
		tick_count end = tick_count::now();

		cout << "Matrica A*B:" << endl;
		cout << A << endl;
		cout << "================================================================" << endl;
		cout <<  "Serijsko racunanje matrice A je trajalo: " << (end - start).seconds() * 1000 << "ms." << endl << endl;

		A = Aprim;
		tick_count start2 = tick_count::now();
		ParallelMultiplication::multiply(A, B);
		tick_count end2 = tick_count::now();
		cout << endl << "A posle paralelnog mnozenja" << endl;
		cout << A << endl;

		cout << "================================================================" << endl;
		cout << "Serijsko racunanje matrice A je trajalo: " << (end - start).seconds() * 1000 << "ms." << endl << endl;

		cout << "=================================================================" << endl;
		cout << "Paralelno racunanje matrice A je trajalo: " << (end2 - start2).seconds() * 1000 << "ms." << endl << endl;

		return 0;
	}
	catch (runtime_error e) {
		cout << e.what() << endl;
		return -1;
	}
	
}