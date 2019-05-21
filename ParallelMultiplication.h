#pragma once
#include"Matrix.h"
#include"MatrixTask.h"
#include"tbb/task.h"

using namespace tbb;
using namespace std;

class ParallelMultiplication {
public:
	
	static void multiply(Matrix& a, Matrix& b);
	static MatrixTask*** zadaci;
	
};

typedef ParallelMultiplication PM;