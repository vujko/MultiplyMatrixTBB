#include "Matrix.h"

Matrix::Matrix(int rows_) :red(rows_), data(red*red, 0)
{
}

int & Matrix::operator()(int i, int j)
{
	return data[i*red + j];
}

ostream & operator<<(ostream & out, const Matrix & m)
{
	int dim_sqaured = m.data.size();
	int dim = sqrt(dim_sqaured);
	string delimeter = "";

	for (int i = 0; i < dim; i++) {
		delimeter = "";
		for (int j = 0; j < dim; j++) {
			out << delimeter << m.data[i * dim + j];
			delimeter = ",";
		}
		out << endl;
	}
	return out;
}
