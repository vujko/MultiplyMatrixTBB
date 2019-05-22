#pragma once
#include<tbb\task.h>
#include<tbb\tbb.h>
#include "ParallelMultiplication.h"

using namespace tbb;
using namespace std;

class MatrixTaskRoot : public task {
public:
	int red;
	Matrix& a;
	empty_task* e;
	int* input1;
	int* input2;
	int* rez;

	MatrixTaskRoot(int red_, Matrix& a_, empty_task* e_) :red(red_), a(a_), e(e_) {
		rez = new int[a.red]{ 0 };
		input1 = new int[a.red];
		input2 = new int[a.red];
		set_ref_count(a.red - 1);
	}

	task* execute() {
		__TBB_ASSERT(ref_count() == 0, NULL);

		int result = 0;
		for (int k = 0; k < a.red; k++) {
			result += input1[k] * input2[k];
		}

		a(red, 0) = result;
		for (int k = 1; k < a.red; k++) {
			a(red, k) = rez[k];
		}

		e->decrement_ref_count();
		return NULL;
	}
};


class MatrixTask : public task {
public:
	int i, j;

	MatrixTaskRoot* successor;
	int* input1;
	int* input2;
	Matrix& a;

	MatrixTask() :i(-1), j(-1),a(Matrix()) {};
	MatrixTask(int i_, int j_, Matrix& a_, MatrixTaskRoot* succ_) :i(i_), j(j_), a(a_), successor(succ_) {

		input1 = new int[a.red];
		input2 = new int[a.red];
	}

	task* execute() {
		

		for (int k = 0; k < a.red; k++) {
			successor->rez[j] += input1[k] * input2[k];
		}
		if (successor->decrement_ref_count() == 0) {
			task::spawn(*successor);
		}
		
		return NULL;

	}
		
	
};