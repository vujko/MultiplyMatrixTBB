#pragma once
#include<tbb\task.h>
#include<tbb\tbb.h>
#include "ParallelMultiplication.h"

using namespace tbb;
using namespace std;

class MatrixTaskRoot : public task {
public:
	int i , j;
	Matrix& a;
	Matrix& b;
	empty_task* e;
	int* rez;

	MatrixTaskRoot( int i_, int j_, Matrix& a_, Matrix& b_, empty_task* e_) : a(a_),b(b_),i(i_), j(j_), e(e_) {
		rez = new int[a.red]{ 0 };
		set_ref_count(a.red - 1);
	}

	task* execute() {
		__TBB_ASSERT(ref_count() == 0, NULL);

		int result = 0;
		for (int k = 0; k < a.red; k++) {
			result += a(i,k) * b(k,j);
		}

		a(i, 0) = result;
		for (int k = 1; k < a.red; k++) {
			a(i, k) = rez[k];
		}

		e->decrement_ref_count();
		return NULL;
	}
};


class MatrixTask : public task {
public:
	int i, j;

	MatrixTaskRoot* successor;
	Matrix& a;
	Matrix& b;

	MatrixTask() :i(-1), j(-1),a(Matrix()), b(Matrix()) {};
	MatrixTask(int i_, int j_, Matrix& a_, Matrix& b_, MatrixTaskRoot* succ_) :i(i_), j(j_), a(a_),b(b_), successor(succ_) {}

	task* execute() {
		

		for (int k = 0; k < a.red; k++) {
			successor->rez[j] += a(i,k) * b(k,j);
		}
		if (successor->decrement_ref_count() == 0) {
			task::spawn(*successor);
		}
		
		return NULL;

	}
		
	
};