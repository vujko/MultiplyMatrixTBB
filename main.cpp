#include <iostream>
#include <vector>
#include <tchar.h>
#include "Matrix.h"
#include <string>
#include <fstream>
using namespace std;

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
	Matrix m = ucitajMatricu("input.txt");
	cout << m;
	return 0;
}