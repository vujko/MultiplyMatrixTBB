#pragma once
#include"Matrix.h"
#include"MatrixTask.h"
#include"tbb/task.h"

using namespace tbb;
using namespace std;

class ParallelMultiplication {
public:
	
	static void multiply(Matrix& a, Matrix& b);
	static MatrixTask*** zadaci_m;
	static MatrixTaskRoot** zadaci_p;
	
};

typedef ParallelMultiplication PM;