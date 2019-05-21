#pragma once
#include <vector>
#include <cstdlib>
#include <math.h>
#include <string>
using namespace std;


class Matrix {
public:
	int red;
	vector<int> data;

	Matrix() :red(0) {

	}
	Matrix(int red_);
	int& operator()(int i, int j);
	friend ostream& operator << (ostream& out,const Matrix& m);


};